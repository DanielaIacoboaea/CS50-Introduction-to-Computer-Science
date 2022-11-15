# CS50’s Introduction to Computer Science

This repository has **problem sets** for each week of the *CS50's Introduction to Computer Science* course.  

It starts by introducing concepts in **`C`** and shifts towards **`Python`**, **`SQL`**, **`HTML`**, **`CSS`** and **`JavaScript`** later in the course. 

The course focuses on teaching how to think algorithmically and solve problems.  

In some **problem sets** you start the project from *scratch*.   

Others focus on reading and *understanding* the existing code, start from there and complete specific tasks.    

---

Topics covered throughout the course:

* Scratch
* [C](#c)
* [Arrays](#arrays) 
* [Algorithms](#algorithms) 
* [Memory](#memory) 
* [Data Structures](#data-structures) 
* [Python](#python) 
* [SQL](#sql) 
* [HTML, CSS, JavaScript](#html-css-javascript) 
* [Flask](#flask) 

### [C](/week1_C)

How to compile and run the code in **pset1**:
* **hello** - Hello, World!:
>    * `make hello`
>    * `./hello`
    
* **mario** - recreate the Mario pyramid in `C`:
>    * `make mario`
>    * `./mario`
    
* **cash** - making change with a greedy algorithm:
>    * `make cash`
>    * `./cash`

* **credit** - check if a credit card is valid:
>    * `make credit`
>    * `./credit`



### [Arrays](/week2_Arrays)

How to compile and run the code in **lab2**:
* **scrabble** - decide which of two Scrabble words is worth more:
>    * `make scrabble`
>    * `./scrabble`

How to compile and run the code in **pset2**:

* **readability** - computes the readability index of some text:
>    * `make readability`
>    * `./readability`
    
* **caesar** - program that encrypts messages using Caesar’s cipher:
>    * `make caesar`
>    * `./caesar 13`

* **substitution** - implements a substitution cipher:
>    * `make substitution`
>    * `./substitution JTREKYAVOGDXPSNCUIZLFBMWHQ`
    
    

### [Algorithms](/week3_Algorithms)

How to compile and run the code in **pset3**:

* **plurality** - a program that runs a plurality election:
>    * `make plurality`
>    * `./plurality Alice Bob Charlie`

* **runoff** - program that runs a runoff election:
>    * `make runoff`
>    * `./runoff Alice Bob Charlie`
    

* **tideman** - program that runs a Tideman election:
>    * `make tideman`
>    * `./tideman Alice Bob Charlie`
    
    
### [Memory](/week4_Memory)

How to compile and run the code in **lab4**:
* **volume** - a program that modifies the volume of an audio file:
>    * `make volume`
>    * `./volume INPUT.wav OUTPUT.wav 2.0`
    
How to compile and run the code in **pset4**:

* **filter** - a program that applies filters to BMPs:
>    * `make filter`
>    * `./filter -g images/yard.bmp out.bmp`


* **recover** - a program that recovers JPEGs from a forensic image:
>    * `make recover`
>    * `./recover card.raw` 


### [Data Structures](/week5_Data_structures)

How to compile and run the code in **lab5**:
* **inheritance** - simulate the inheritance of blood types for family members:
>    * `make inheritance`
>    * `./inheritance`
    
How to compile and run the code in **pset5**:

* **speller** - a program that spell-checks a file:
>    * `make speller`
>    * `./speller texts/lalaland.txt` 



### [Python](/week6_Python)

How to run the code in **lab6**:
* **tournament** - a program to run simulations of the FIFA World Cup:
>    * `python3 tournament.py 2018m.csv`

How to run the code in **pset6**:

* **hello**:
>    * `python3 hello.py`
    
* **mario** - recreate the Mario pyramid in `C`:
>    * `python3 mario.py`
    
* **cash** - making change with a greedy algorithm:
>    * `python3 cash.py`

* **credit** - check if a credit card is valid:
>    * `python3 credit.py`

* **readability** - computes the readability index of some text:
>    * `python3 readability.py`

* **DNA** - implement a program that identifies a person based on their DNA:
>    * `python3 dna.py databases/large.csv sequences/5.txt`
    
    

### [SQL](/week7_SQL)

How to run the code in **lab7**:

* **songs** - write `SQL` queries to answer questions about a database of songs:
>    * `cat filename.sql | sqlite3 songs.db`


How to run the code in **pset7**:
* **movies** - write `SQL` queries to answer questions about a database of movies:
>    * `cat filename.sql | sqlite3 movies.db > output.txt`

* **fiftyville** - write `SQL` queries to solve a mystery:
>    * `cat log.sql | sqlite3 fiftyville.db`
>    * read `answers.txt`


### [HTML, CSS, JavaScript](/week8_HTML-CSS-Javascript)

How to run the code in **lab8**:

* **trivia** - write a webpage that lets users answer trivia questions:
>    * open `index.html` in a browser

How to run the code in **pset8**:

* **homepage** - build a simple homepage using `HTML`, `CSS`, and `JavaScript`:
>    * open `index.html` in a browser


### [Flask](/week9_Flask)


How to run the code in **lab9**:

* **birthdays** - create a web application to keep track of friends’ birthdays:
>    * `flask run`

How to run the code in **pset9**:

* **finance** - implement a website via which users can buy and sell stocks:
>    *  `pip3 install -r requirements.txt`
>    * `flask run`



