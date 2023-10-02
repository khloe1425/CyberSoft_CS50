import re
import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from werkzeug.security import generate_password_hash, check_password_hash
from helpers import apology, login_required, lookup, usd, get_time, check_password
from flask_session import Session


app = Flask(__name__)

app.jinja_env.filters["usd"] = usd

app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

db = SQL("sqlite:///finance.db")

if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


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
    """Show portfolio of stocks."""

    user_id = session["user_id"]
    portfolio = db.execute("SELECT * FROM portfolios WHERE user_id = ?", user_id)
    cash_left = db.execute("SELECT cash FROM users WHERE id = ?", user_id)

    if cash_left and "cash" in cash_left[0]:
        cash_left = float(cash_left[0]["cash"])
    else:
        cash_left = 0.0

    total_amount = cash_left

    try:
        for stock in portfolio:
            symbol = stock["symbol"]
            stock_info = lookup(symbol)

            current_price = float(stock_info["price"])
            stock_value = current_price * stock["shares"]

            stock.update({"current_price": current_price, "stock_value": stock_value})
            total_amount += float(stock["stock_value"])
    except (ValueError, LookupError):
        return apology("Failed to update stock prices!")

    return render_template(
        "index.html",
        portfolio=portfolio,
        cash_left=cash_left,
        total_amount=total_amount,
    )


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock."""

    if request.method == "POST":
        user_id = session["user_id"]

        symbol = request.form.get("symbol")
        stock = lookup(symbol)
        shares = request.form.get("shares")

        if not symbol or not stock:
            return apology("Symbol is not valid!")

        if not shares.isdigit():
            return apology("Number of shares must be a positive digit!")

        transaction_value = int(shares) * stock["price"]
        user_cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
        user_cash = user_cash[0]["cash"]

        if user_cash < transaction_value + 1:
            return apology("Not enough money!", 401)

        update_user_cash = user_cash - transaction_value
        db.execute("UPDATE users SET cash = ? WHERE id = ?", update_user_cash, user_id)

        balance = f"${update_user_cash:,.2f} (-${transaction_value:,.2f})"

        db.execute(
            "INSERT INTO portfolios (user_id, name, symbol, shares, paid_price, current_price, date, stock_value) VALUES (?, ?, ?, ?, ?, ?, ?, ?)",
            user_id,
            stock["name"],
            symbol,
            shares,
            stock["price"],
            stock["price"],
            get_time(),
            stock["price"],
        )

        db.execute(
            "INSERT INTO history (user_id, name, symbol, shares, action, balance, date) VALUES (?, ?, ?, ?, ?, ?, ?)",
            user_id,
            stock["name"],
            symbol,
            shares,
            "BOUGHT",
            balance,
            get_time(),
        )

        flash(f"Successfully bought {shares} shares of {symbol}!")
        return redirect("/")

    return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions."""

    user_id = session["user_id"]
    portfolio = db.execute("SELECT * FROM history WHERE user_id = ?", user_id)

    return render_template("history.html", portfolio=portfolio)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in."""

    session.clear()

    if request.method == "POST":
        if not request.form.get("username"):
            return apology("Must provide username!", 403)

        if not request.form.get("password"):
            return apology("Must provide password!", 403)

        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        session["user_id"] = rows[0]["id"]

        return redirect("/")

    return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out."""

    session.clear()

    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    if request.method == "POST":
        stock = lookup(str(request.form.get("symbol")))

        if not stock:
            return apology("Invalid symbol!")

        stock["price"] = usd(stock["price"])

        return render_template("quoted.html", stock=stock)

    return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user."""

    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        if any(not field for field in [username, password, confirmation]):
            return apology("Fields cannot be empty!")

        if len(username) < 4:
            return apology("Username must be at least 4 characters long!", 403)

        if not username.isalnum():
            return apology("Username must contain only characters and digits!", 403)

        if len(password) < 8:
            return apology("Password must be at least 8 characters long!", 403)
        if (
            not re.search("[a-zA-Z]", password)
            or not re.search("[0-9]", password)
            or not re.search("[!@#$%^&*()]", password)
        ):
            return apology("Password must contain characters, digits and symbols!", 403)

        if password != confirmation:
            return apology("Passwords do not match!", 400)

        if len(db.execute("SELECT * FROM users WHERE username = ?", username)) > 0:
            return apology("Username already taken!", 400)

        hashed_password = generate_password_hash(password)
        db.execute(
            "INSERT INTO users (username, hash) VALUES (?, ?)",
            username,
            hashed_password,
        )

        rows = db.execute("SELECT * FROM users WHERE username = ?", username)
        session["user_id"] = rows[0]["id"]

        return redirect("/")

    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock."""

    user_id = session["user_id"]
    portfolio = db.execute("SELECT * FROM portfolios WHERE user_id = ?", user_id)

    if request.method == "POST":
        symbol = request.form.get("symbol")
        stock = lookup(symbol)
        shares = int(request.form.get("shares"))

        owned_stock = db.execute(
            "SELECT shares FROM portfolios WHERE user_id = ? AND symbol = ?",
            user_id,
            symbol,
        )

        if not owned_stock:
            return apology(f"You don't own any shares of {symbol}!")

        current_shares = sum([stock["shares"] for stock in owned_stock])
        if current_shares < shares:
            return apology("You don't have enough shares to sell!")

        cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
        cash = cash[0]["cash"]
        current_price = stock["price"]
        cash += shares * current_price

        for info in owned_stock:
            if info["shares"] > shares:
                db.execute(
                    "UPDATE portfolios SET shares = ? WHERE user_id = ? AND symbol = ?",
                    info["shares"] - shares,
                    user_id,
                    symbol,
                )
            else:
                db.execute(
                    "DELETE FROM portfolios WHERE user_id = ? AND symbol = ?",
                    user_id,
                    symbol,
                )

        balance = f"${cash:,.2f} (+${(shares * current_price):,.2f})"

        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash, user_id)

        db.execute(
            "INSERT INTO history (user_id, name, symbol, shares, action, balance, date) VALUES (?, ?, ?, ?, ?, ?, ?)",
            user_id,
            stock["name"],
            symbol,
            shares,
            "SOLD",
            balance,
            get_time(),
        )

        flash(f"Successfully sold {shares} shares of {symbol}!")
        return redirect("/")

    return render_template("sell.html", portfolio=portfolio)


@app.route("/deposit", methods=["GET", "POST"])
@login_required
def deposit():
    """Deposit funds to account."""

    if request.method == "POST":
        user_id = session["user_id"]

        amount = int(request.form.get("sum"))
        account = db.execute("SELECT * FROM users WHERE id = ?", user_id)

        check_password(account[0]["hash"], request.form.get("password"))

        cash = account[0]["cash"] + amount
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash, user_id)

        flash(f"Successfully added ${amount} to your balance!")
        return redirect("/")

    return render_template("deposit.html")


@app.route("/withdraw", methods=["GET", "POST"])
@login_required
def withdraw():
    """Withdraw funds from account."""

    if request.method == "POST":
        user_id = session["user_id"]

        amount = int(request.form.get("sum"))
        account = db.execute("SELECT * FROM users WHERE id = ?", user_id)

        check_password(account[0]["hash"], request.form.get("password"))

        if amount > account[0]["cash"]:
            return apology("Cannot withdraw more than cash left!")

        cash = account[0]["cash"] - amount
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash, user_id)

        flash(f"Successfully withdrew ${amount} from your balance!")
        return redirect("/")

    return render_template("withdraw.html")
