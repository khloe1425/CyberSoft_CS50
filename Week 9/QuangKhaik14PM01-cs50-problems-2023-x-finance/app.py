import os
import datetime

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
    # Get user's current cash balance
    user_cash = db.execute("SELECT cash FROM users WHERE id = ?", session["ufiser_id"])[0]["cash"]

    # Get user's stocks and their current prices
    stocks = db.execute("SELECT symbol, SUM(shares) as total_shares FROM transactions WHERE user_id = ? GROUP BY symbol HAVING total_shares > 0", session["user_id"])



    # Calculate the total value of each stock
    portfolio = []
    total_value = user_cash

    for stock in stocks:
        stock_info = lookup(stock["symbol"])
        total_shares = stock["total_shares"]
        total_value += total_shares * stock_info["price"]
        portfolio.append({
            "symbol": stock_info["symbol"],
            "name": stock_info["name"],
            "price": stock_info["price"],
            "total_shares": total_shares,
            "total_value": total_shares * stock_info["price"]
        })

    return render_template("index.html", user_cash=user_cash, total_value=total_value, portfolio=portfolio)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = int(request.form.get("shares"))

        # Validate stock symbol
        if not symbol:
            return apology("must provide stock symbol", 403)

        # Validate number of shares
        if shares < 1:
            return apology("must provide a positive number of shares", 403)

        # Lookup the stock symbol
        stock_info = lookup(symbol)
        if not stock_info:
            return apology("invalid stock symbol", 403)

        # Check if user can afford the purchase
        user_cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
        total_cost = stock_info["price"] * shares
        if user_cash < total_cost:
            return apology("not enough cash to buy the specified number of shares", 403)

        # Record the purchase in the database
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price, transaction_type, timestamp) VALUES (?, ?, ?, ?, ?, ?)",
                   session["user_id"], stock_info["symbol"], shares, stock_info["price"], "buy", datetime.datetime.now())

        # Update user's cash balance
        db.execute("UPDATE users SET cash = cash - ? WHERE id = ?", total_cost, session["user_id"])

        # Redirect to the home page
        return redirect("/")

    else:
        return render_template("buy.html")



@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    # Get user's transaction history
    transactions = db.execute("SELECT symbol, shares, price, transaction_type, timestamp FROM transactions WHERE user_id = ? ORDER BY timestamp DESC",
                              session["user_id"])

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
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

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
        if not symbol:
            return apology("must provide stock symbol", 403)

        # Lookup the stock symbol
        stock_info = lookup(symbol)
        if not stock_info:
            return apology("invalid stock symbol", 403)

        return render_template("quoted.html", stock_info=stock_info)

    else:
        return render_template("quote.html")



@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # Validate username
        if not username:
            return apology("must provide username", 403)

        # Validate password
        if not password or password != confirmation:
            return apology("passwords do not match", 403)

        # Hash the password
        hashed_password = generate_password_hash(password)

        # Insert user into the database
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hashed_password)

        # Log in the user automatically
        user_id = db.execute("SELECT id FROM users WHERE username = ?", username)[0]["id"]
        session["user_id"] = user_id

        # Redirect to the home page
        return redirect("/")

    else:
        return render_template("register.html")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = int(request.form.get("shares"))

        # Validate stock symbol
        if not symbol:
            return apology("must select a stock to sell", 403)

        # Validate number of shares
        if shares < 1:
            return apology("must provide a positive number of shares", 403)

        # Check if user owns enough shares to sell
        user_shares = db.execute("SELECT SUM(shares) as total_shares FROM transactions WHERE user_id = ? AND symbol = ? GROUP BY symbol",
                                 session["user_id"], symbol)
        if not user_shares or user_shares[0]["total_shares"] < shares:
            return apology("not enough shares to sell", 403)

        # Lookup the stock symbol
        stock_info = lookup(symbol)
        if not stock_info:
            return apology("invalid stock symbol", 403)

        # Record the sale in the database
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price, transaction_type, timestamp) VALUES (?, ?, ?, ?, ?, ?)",
                   session["user_id"], stock_info["symbol"], -shares, stock_info["price"], "sell", datetime.datetime.now())

        # Update user's cash balance
        db.execute("UPDATE users SET cash = cash + ? WHERE id = ?", stock_info["price"] * shares, session["user_id"])

        # Redirect to the home page
        return redirect("/")

    else:
        # Get user's stocks and their current prices
        stocks = db.execute("SELECT symbol FROM transactions WHERE user_id = ? GROUP BY symbol HAVING SUM(shares) > 0", session["user_id"])

        # Get user's portfolio for selling
        portfolio = []
        for stock in stocks:
            stock_info = lookup(stock["symbol"])
            portfolio.append({
                "symbol": stock_info["symbol"],
                "name": stock_info["name"],
                "total_shares": db.execute("SELECT SUM(shares) as total_shares FROM transactions WHERE user_id = ? AND symbol = ? GROUP BY symbol",
                                          session["user_id"], stock_info["symbol"])[0]["total_shares"]
            })

        return render_template("sell.html", portfolio=portfolio)

