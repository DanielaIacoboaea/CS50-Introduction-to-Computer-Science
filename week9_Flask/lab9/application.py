import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")

@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":

        # Add the user's entry into the database
        add_name = request.form.get("name")
        add_month = request.form.get("month")
        add_day = request.form.get("day")

        db.execute("INSERT INTO birthdays (name, month, day) VALUES (?, ?, ?)", add_name, add_month, add_day)
        return redirect("/")

    else:

        # Display the entries in the database on index.html
        entries = db.execute("SELECT * FROM birthdays")

        return render_template("index.html", entries=entries)


