"""
TimeBoard Time Service (TBTS)

A lightweight HTTP time service designed for legacy Palm OS devices.

Author: @coloraturip
API: v1
License: MIT
"""

from flask import Flask, jsonify
from datetime import datetime, timezone

# ---------------------------------------------------------
# Configuration
# ---------------------------------------------------------

HOST = "0.0.0.0"
PORT = 80

SERVICE_NAME = "TimeBoard Time Service"
SERVICE_SHORT_NAME = "TBTS"
SERVICE_VERSION = "1.0"

app = Flask(__name__)


# ---------------------------------------------------------
# API v1 response builders
# ---------------------------------------------------------

def build_v1_utc_response(now):
    """Builds the UTC response for API v1."""

    return {
        "utc_datetime": now.isoformat(timespec="seconds").replace("+00:00", "Z"),
        "unixtime": int(now.timestamp())
    }


# ---------------------------------------------------------
# Customize HTTP headers
# ---------------------------------------------------------

@app.after_request
def customize_headers(response):

    # Hide Werkzeug/Python version
    response.headers["Server"] = f"{SERVICE_SHORT_NAME}/{SERVICE_VERSION}"

    return response


# ---------------------------------------------------------
# Root endpoint
# ---------------------------------------------------------

@app.route("/")
def index():

    return jsonify({
        "service": SERVICE_NAME,
        "short_name": SERVICE_SHORT_NAME,
        "version": SERVICE_VERSION,
        "status": "online",
        "description": "Lightweight HTTP time service for legacy Palm OS devices.",
        "documentation": "/api"
    })


# ---------------------------------------------------------
# API information
# ---------------------------------------------------------

@app.route("/api")
def api():

    return jsonify({
        "latest": "v1",
        "versions": {
            "v1": {
                "utc": "/api/v1/utc"
            }
        }
    })


# ---------------------------------------------------------
# API v1 - UTC time
# ---------------------------------------------------------

@app.route("/api/v1/utc")
def api_v1_utc():

    now = datetime.now(timezone.utc)

    return jsonify(build_v1_utc_response(now))


# ---------------------------------------------------------
# Main
# ---------------------------------------------------------

if __name__ == "__main__":
    app.run(host=HOST, port=PORT)