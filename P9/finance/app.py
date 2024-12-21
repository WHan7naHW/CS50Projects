import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # Get user ID
    user_id = session["user_id"]

    # Query the user's stocks (aggregate shares for each stock)
    rows = db.execute("""
        SELECT symbol, SUM(shares) as total_shares
        FROM transactions
        WHERE user_id = ?
        GROUP BY symbol
        HAVING total_shares > 0
    """, user_id)

    # Initialize portfolio and grand total
    portfolio = []
    stocks_total_value = 0

    # Fetch current stock prices and calculate total values
    for row in rows:
        stock = lookup(row["symbol"])
        total_value = row["total_shares"] * stock["price"]
        portfolio.append({
            "symbol": row["symbol"],
            "shares": row["total_shares"],
            "price": stock["price"],
            "total": total_value
        })
        stocks_total_value += total_value

    # Get the user's current cash balance
    user_cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]

    # Calculate the grand total
    grand_total = user_cash + stocks_total_value

    # Render the index page with portfolio data
    return render_template("index.html", portfolio=portfolio, cash=user_cash, total=grand_total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Get user ID
        user_id = session["user_id"]

        # Get symbol
        symbol = request.form.get("symbol")
        # Ensure symbol was submitted
        if not symbol:
            return apology("invalid symbol", 400)

        # Get shares
        shares = request.form.get("shares")
        # Ensure shares was submitted
        if not shares:
            return apology("missing shares", 400)
        try:
            shares = int(shares)

            # Check if shares is positive
            if shares <= 0:
                return apology("invalid shares", 400)

        except ValueError:
            return apology("invalid shares", 400)

        # Look up stock
        stock = lookup(symbol)
        if not stock:
            return apology("invalid symbol", 400)

        # Query database for remained cash of user
        rows = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
        cash = rows[0]["cash"]

        # Calculate total cost
        total_cost = stock["price"] * shares
        # Ensure user has enough cash to buy it
        if total_cost > cash:
            return apology("can't afford", 400)

        # Record the transaction: who bought what at what price and when
        db.execute(
            "INSERT INTO transactions (user_id, symbol, price, shares, total) VALUES (?, ?, ?, ?, ?)",
            user_id, stock["symbol"], stock["price"], int(shares), total_cost
        )

        # Update user's cash
        db.execute("UPDATE users SET cash = cash - ? WHERE id = ?", total_cost, user_id)

        # Pop up flash message
        flash("Bought!")

        # Redirect user to home page
        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    # Get user ID
    user_id = session["user_id"]

    # Query the user's stocks
    history = db.execute("""
        SELECT symbol, shares, price, timestamp
        FROM transactions
        WHERE user_id = ?
        ORDER BY timestamp DESC
    """, user_id)

    # Render history page
    return render_template("history.html", history=history)


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
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Pop up flash message
        flash("Welcome!")

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

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        symbol = request.form.get("symbol")

        # Ensure symbol was submitted
        if not symbol:
            return apology("invalid symbol", 400)

        # Get quoted symbol data
        quote_data = lookup(symbol)

        # Ensure
        if not quote_data:
            return apology("invalid symbol", 400)

        # Render quoted page
        return render_template("quoted.html", quote_data=quote_data)

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Get username and hash the password for security
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # Ensure username was submitted
        if not username:
            return apology("missing username", 400)

        # Ensure 1st password was submitted
        elif not password:
            return apology("missing password", 400)

        # Ensure 2nd password matches
        elif confirmation != password:
            return apology("password don't match", 400)

        # Hash the password for security
        hashed_password = generate_password_hash(password)

        # Insert new user into db
        try:
            db.execute(
                "INSERT INTO users (username, hash) VALUES (?, ?)", username, hashed_password
            )

            # Pop up flash message
            flash("Registered!")

            # Redirect user to home page
            return redirect("/")

        except ValueError:
            return apology("username taken", 400)

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Get user ID
        user_id = session["user_id"]

        # Get stock symbol
        symbol = request.form.get("symbol")
        # Ensure symbol was submitted
        if not symbol:
            return apology("missing symbol", 400)

        # Get shares_to_sell
        shares_to_sell = request.form.get("shares")
        # Ensure shares was submitted
        if not shares_to_sell:
            return apology("missing shares", 400)
        try:
            shares_to_sell = int(shares_to_sell)
            if shares_to_sell <= 0:
                return apology("shares must be positive", 400)
        except ValueError:
            return apology("invalid shares", 400)

        # Query the database for user's total shares of the stock
        row = db.execute("""
            SELECT SUM(shares) as total_shares
            FROM transactions
            WHERE user_id = ? AND symbol = ?
            GROUP BY symbol
        """, user_id, symbol)

        # Ensure user has enough shares to sell
        if not row or row[0]["total_shares"] < shares_to_sell:
            return apology("too many shares", 400)

        # Lookup the current price of the stock
        stock = lookup(symbol)
        if not stock:
            return apology("invalid symbol", 400)

        # Calculate the total sale value
        sale_value = stock["price"] * shares_to_sell

        # Update the transactions table to record the sale (negative shares)
        db.execute("""
            INSERT INTO transactions (user_id, symbol, shares, price, total)
            VALUES (?, ?, ?, ?, ?)
        """, user_id, symbol, -shares_to_sell, stock["price"], -sale_value)

        # Update the user's cash balance
        db.execute("""
            UPDATE users
            SET cash = cash + ?
            WHERE id = ?
        """, sale_value, user_id)

        # Pop up flash message
        flash("Sold!")

        # Redirect to home page
        return redirect("/")

    # User reached route via GET
    else:
        # Query user's stocks' symbol for the select menu
        stocks = db.execute("""
            SELECT symbol, SUM(shares) as total_shares
            FROM transactions
            WHERE user_id = ?
            GROUP BY symbol
            HAVING total_shares > 0
        """, session["user_id"])
        return render_template("sell.html", stocks=stocks)


@app.route("/changepw", methods=["GET", "POST"])
@login_required
def changepw():
    """Change user's password"""

    if request.method == "POST":
        # Get user ID
        user_id = session["user_id"]

        # Get the old and new passwords
        old_password = request.form.get("old_password")
        new_password = request.form.get("new_password")
        confirm_password = request.form.get("confirm_password")

        # Ensure the old password, new password, and confirmation are provided
        if not old_password or not new_password or not confirm_password:
            return apology("missing values", 400)

        # Query the user's current password hash from the database
        user = db.execute("SELECT * FROM users WHERE id = ?", user_id)

        # Ensure the old password matches the user's current password
        if not check_password_hash(user[0]["hash"], old_password):
            return apology("incorrect old password", 400)

        # Ensure the new password and old password are not the same
        if new_password == old_password:
            return apology("new password is the same as the old one", 400)

        # Ensure the new password matches the confirmation
        if new_password != confirm_password:
            return apology("new password don't match", 400)

        # Hash the new password
        hashed_password = generate_password_hash(new_password)

        # Update the user's password in the database
        db.execute("UPDATE users SET hash = ? WHERE id = ?", hashed_password, user_id)

        # Provide a success message
        flash("Password changed successfully!")

        # Redirect to the home page or a suitable page
        return redirect("/")

    else:
        return render_template("changepw.html")
