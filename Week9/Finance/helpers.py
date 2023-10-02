import os
import urllib.parse
import requests

from flask import redirect, render_template, session
from werkzeug.security import check_password_hash
from datetime import datetime
from functools import wraps


def apology(message, code=400):

    def escape(s):
        for old, new in [
            ("-", "--"),
            (" ", "-"),
            ("_", "__"),
            ("?", "~q"),
            ("%", "~p"),
            ("#", "~h"),
            ("/", "~s"),
            ('"', "''"),
        ]:
            s = s.replace(old, new)
        return s

    if isinstance(message, str):
        message = escape(message)
    else:
        message = "Error occured!"

    return render_template("apology.html", top=code, bottom=message), code


def login_required(f):
    @wraps(f)
    def decorated_function(*args, **kwargs):
        if session.get("user_id") is None:
            return redirect("/login")

        return f(*args, **kwargs)

    return decorated_function


def lookup(symbol):
    try:
        api_key = os.environ.get("API_KEY")
        url = f"https://cloud.iexapis.com/stable/stock/{urllib.parse.quote_plus(symbol)}/quote?token={api_key}"
        response = requests.get(url)
        response.raise_for_status()
    except requests.RequestException:
        return None

    try:
        quote = response.json()
        return {
            "name": quote["companyName"],
            "price": float(quote["latestPrice"]),
            "symbol": quote["symbol"],
        }
    except (KeyError, TypeError, ValueError):
        return None


def usd(value):
    return f"${value:,.2f}"


def get_time():
    return datetime.now().strftime("%d-%m-%Y %H:%M:%S")


def check_password(first_password, second_password):
    if not check_password_hash(first_password, second_password):
        return apology("Passwords do not match!", code=401)
