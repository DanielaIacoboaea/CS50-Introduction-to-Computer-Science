import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime, date

from helpers import apology, login_required, lookup, usd, user_cash

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # query the transactions table for active shares number
    assets = db.execute("""
        SELECT
            SUM(transactions.shares) AS shares, stocks.symbol, stocks.name
        FROM
            transactions
        JOIN stocks ON transactions.stock_id = stocks.stocks_id
        JOIN users ON stocks.username_id = users.id
        WHERE
            users.id = ?
        GROUP BY stocks.symbol
        """, session["user_id"])

    userCash = user_cash(session["user_id"], db)

    # find out the total value for the current stocks
    stocksTotalWorth = 0

    # update the stock's price to reflect the current price in the market
    for stock in assets:
        # don't add to total price stocks that the user doesn't own anymore
        if stock["shares"] > 0:
            # get up to date price
            updatedStockInfo = lookup(stock["symbol"])
            stock["price"] = updatedStockInfo["price"]
            stock["total"] = stock["price"] * stock["shares"]
            stocksTotalWorth = stocksTotalWorth + stock["total"]

    stocksTotalWorth = stocksTotalWorth + userCash[0]["cash"]

    return render_template("index.html", assets=assets, userCash=userCash[0]["cash"], stocksTotalWorth=stocksTotalWorth)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == "POST":
        symbol = request.form.get("symbol")

        # check if the input shares is numeric
        if request.form.get("shares").isdigit() == False:
            return apology("Invalid shares type", 400)

        shares = float(request.form.get("shares"))

        userCash = user_cash(session["user_id"], db)

        symbol = symbol.strip().upper()
        updatedStockInfo = lookup(symbol)

        # check if the shares number is fractional
        if shares.is_integer() == False:
            return apology("Invalid shares type", 400)

        try:
            symbol == updatedStockInfo["symbol"]
        except TypeError:
            return apology("Stock Symbol not found", 400)

        # check if the user affords to buy the number of shares selected
        if shares * updatedStockInfo["price"] <= userCash[0]["cash"]:
            # save the purchase in the database

            # check if the stock is already saved in stocks table, otherwise create new entry
            stockInStocks = db.execute("""
                            SELECT
                                stocks.stocks_id
                            FROM
                                stocks
                            JOIN users ON stocks.username_id = users.id
                            WHERE
                                stocks.symbol = ? AND users.id=?
                            """, symbol, session["user_id"])

            if len(stockInStocks) == 1:
                stock_id = stockInStocks[0]["stocks_id"]
            else:
                db.execute("""
                    INSERT INTO
                        stocks (symbol, name, username_id)
                    VALUES (?, ?, ?)
                    """, symbol, updatedStockInfo["name"], session["user_id"])
                stockInStocks = db.execute("""
                                SELECT
                                    stocks.stocks_id
                                FROM
                                    stocks
                                JOIN users ON stocks.username_id = users.id
                                WHERE
                                    stocks.symbol = ? AND users.id=?
                                """, symbol, session["user_id"])
                stock_id = stockInStocks[0]["stocks_id"]

            db.execute("""
                INSERT INTO
                        transactions (stock_id, shares, price, date)
                VALUES (?, ?, ?, ?)
                """, stock_id, shares, updatedStockInfo["price"], datetime.now().date())

            db.execute("""
                UPDATE
                    users
                SET
                    cash=?
                WHERE id=?
                """, userCash[0]["cash"]-(shares * updatedStockInfo["price"]), session["user_id"])
            return redirect("/")
        else:
            return apology("not enough cash", 400)
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    # query users and transactions tables to provide history of transactions for the current user
    transactions = db.execute("""
        SELECT
            stocks.symbol, stocks.name, transactions.shares, transactions.price, transactions.date
        FROM
            transactions
        JOIN stocks ON transactions.stock_id = stocks.stocks_id
        JOIN users ON stocks.username_id = users.id
        WHERE
            users.id = ?
        ORDER BY
            transactions.date
        """, session["user_id"])

    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("""
                SELECT * FROM
                    users
                WHERE
                    username = ?
                """, request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    if request.method == "POST":
        symbol = request.form.get("symbol")

        # trim whitespace and convert to uppercase the user input
        symbol = symbol.strip().upper()
        searchSymbol = lookup(symbol)

        # check if the user input is empty
        if not symbol:
            return apology("must provide symbol", 400)

        # check if the symbol provided exists and send info to the template
        try:
            if symbol == searchSymbol["symbol"]:
                return render_template("quoted.html", stock=searchSymbol)
        except TypeError:
            return apology("must provide symbol", 400)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":

        username = request.form.get("username")
        password = request.form.get("password")
        passwordConfirmation = request.form.get("confirmation")

        # query users table to ckeck if the username is already taken
        testIfUsername = db.execute("""
                            SELECT * FROM users
                            WHERE
                                username=(?)
                            """, username)

        # test if username provided is empty or the username already exists in the database
        if not username or len(testIfUsername) != 0:
            return apology("Invalid Username", 400)

        # test if the password is empty or it does not match with the confirmation
        if not password or password != passwordConfirmation:
            return apology("Invalid Password", 400)

        # add user to the database
        db.execute("""
        INSERT INTO
            users(username, hash)
        VALUES(?, ?)
        """, username, generate_password_hash(password))

        flash("You were successfully registered!")
        return render_template("login.html")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    if request.method == "POST":

        symbol = request.form.get("symbol")
        shares = float(request.form.get("shares"))

        userCash = user_cash(session["user_id"], db)

        symbol = symbol.strip().upper()
        updatedStockInfo = lookup(symbol)

        try:
            symbol == updatedStockInfo["symbol"]
        except TypeError:
            error = "Stock Symbol not found"
            flash(error)
            return render_template("sell.html")

        # query database to check if the user has the amount of shares that wants to sell
        assetNumber = db.execute("""
        SELECT
            SUM(transactions.shares) AS shares, stocks.stocks_id
        FROM
            transactions
        JOIN stocks ON transactions.stock_id = stocks.stocks_id
        JOIN users ON stocks.username_id = users.id
        WHERE
            stocks.symbol = ? AND users.id = ?
        """, symbol, session["user_id"])

        # save the stock sell in the database, otherwise alert the user
        # multiply the shares * -1 to mark a sale
        if assetNumber[0]["shares"] >= shares:

            db.execute("""
            INSERT INTO
                transactions (stock_id, shares, price, date)
            VALUES (?, ?, ?, ?)
            """, assetNumber[0]["stocks_id"], (shares * -1), updatedStockInfo["price"], datetime.now().date())

            # update the user's cash after the sell was made
            db.execute("""
                UPDATE
                    users
                SET
                    cash=?
                WHERE id=?
                """, userCash[0]["cash"]+(shares * updatedStockInfo["price"]), session["user_id"])
            return redirect("/")
        else:
            return apology("not enough shares", 400)

    else:

        assets = db.execute("""
        SELECT
            SUM(transactions.shares) AS shares, stocks.symbol, stocks.name
        FROM
            transactions
        JOIN stocks ON transactions.stock_id = stocks.stocks_id
        JOIN users ON stocks.username_id = users.id
        WHERE
            users.id = ?
        GROUP BY stocks.symbol
        """, session["user_id"])

        return render_template("sell.html", stocks=assets)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
