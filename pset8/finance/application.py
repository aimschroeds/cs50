import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash
# using datetime module
import datetime

from helpers import apology, login_required, lookup, usd

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

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        return apology("not yet supported", 403)

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        rows = db.execute("SELECT symbol, SUM(number) AS number FROM purchases WHERE user_id = ? GROUP BY 1", session["user_id"])
        all_stock_value = 0
        get_cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        cash = usd(get_cash[0]['cash'])
        for row in rows:
            stock_data = lookup(row['symbol'])
            current_stock_price = stock_data['price']
            company_name = stock_data['name']
            row['current_stock_price'] = usd(current_stock_price)
            row['company_name'] = company_name
            stock_value = row['number'] * current_stock_price
            row['stock_value'] = usd(row['number'] * current_stock_price)
            all_stock_value = all_stock_value + stock_value
        all_holdings_value = usd(all_stock_value + (get_cash[0]['cash']))
        all_stock_value = usd(all_stock_value)
        print(rows)
        return render_template("index.html", rows=rows, cash=cash, all_holdings_value=all_holdings_value)

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure stock symbol was submitted
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("must provide stock ticker symbol", 403)

        stock_data = lookup(symbol)

        if stock_data == None:
            return apology("must provide valid stock ticker symbol", 403)

        elif (not request.form.get("number").isnumeric()):
            return apology("please provide a number using only digits from 0-9 to indicate how many shares you want to buy", 403)

        price = stock_data['price']
        number_of_stock = int(request.form.get("number"))
        total_cost = price * number_of_stock

        if number_of_stock == 0:
            return apology("please provide a positive number", 403)

        # Query database for users cash amount
        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        cash_available = cash[0]['cash']
        if total_cost > cash_available:
            return apology("funds depleted, not enough cash for this purchase", 403)
        else:
            timestamp = datetime.datetime.now()
            symbol = stock_data['symbol']
            db.execute("UPDATE users SET cash = ? WHERE id = ?", cash_available - total_cost , session["user_id"])
            db.execute("INSERT INTO purchases (user_id, symbol, price, type, date, number) VALUES(?, ?, ?, ?, ?, ?)",
                    session["user_id"], symbol, price, 'purchase', timestamp, number_of_stock)
            flash("Purchase complete")
            return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    rows = db.execute("SELECT * FROM purchases WHERE user_id = ?", session["user_id"])
    for row in rows:
        stock_data = lookup(row['symbol'])
        row['company_name'] = stock_data['name']
        row['price'] = usd(row['price'])
    print(rows)
    return render_template("history.html", rows=rows)


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
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        flash('Login Successful')
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

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure stock symbol was submitted
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("must provide stock ticker symbol", 403)

        stock_data = lookup(symbol)

        if stock_data == None:
            return apology("must provide valid stock ticker symbol", 403)

        return render_template("quoted.html", stock_data=stock_data)

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Ensure password-confirm was submitted
        elif not request.form.get("password-confirm"):
            return apology("must provide password confirmation", 403)

        # Ensure password and password-confirm are the same
        elif not request.form.get("password") == request.form.get("password-confirm"):
            return apology("password and confirm password should be the same", 403)

        # Set username
        username=request.form.get("username")

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", username)
        if len(rows) == 1:
            return apology("username already exists", 403)

        # Hash password
        password_hashed = generate_password_hash(request.form.get("password-confirm"))

        # Insert user into db
        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username, password_hashed)

        # Redirect user to login page
        flash('Registration Successful - You May Now Login')
        return redirect("/login")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure stock symbol was submitted
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("must provide stock ticker symbol", 403)

        stock_data = lookup(symbol)

        if stock_data == None:
            return apology("must provide valid stock ticker symbol", 403)

        elif not (request.form.get("number").isnumeric()):
            return apology("please provide a positive number using only digits from 0-9 to indicate how many shares you want to buy", 403)

        price = stock_data['price']
        number_of_stock = int(request.form.get("number"))
        total_cost = price * number_of_stock
        symbol = stock_data['symbol']

        if number_of_stock == 0:
            return apology("please provide a positive number", 403)

        # Query database for users amount of this stock
        get_number_stock_available = db.execute("SELECT SUM(number) AS number FROM purchases WHERE user_id = ? AND symbol = ?", session["user_id"], symbol)
        print(get_number_stock_available)
        stock_available = get_number_stock_available[0]['number']
        print(number_of_stock, stock_available)
        if stock_available is None:
            return apology("you don't own any of this stock", 403)
        elif number_of_stock > stock_available:
            return apology("you are trying to sell more shares than you own", 403)
        else:
            cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
            cash_available = cash[0]['cash']
            timestamp = datetime.datetime.now()
            symbol = stock_data['symbol']
            db.execute("UPDATE users SET cash = ? WHERE id = ?", cash_available + total_cost , session["user_id"])
            db.execute("INSERT INTO purchases (user_id, symbol, price, type, date, number) VALUES(?, ?, ?, ?, ?, ?)",
                    session["user_id"], symbol, price, 'sale', timestamp, (number_of_stock*-1))
            flash("Sale complete")
            return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("sell.html")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
