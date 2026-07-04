from flask import Flask, jsonify
from datetime import datetime, timezone

app = Flask(__name__)


# ---------------------------------------------------------
# Construye la respuesta UTC
# ---------------------------------------------------------
def build_utc_response(now):

    return {
        "utc_datetime": now.isoformat(timespec="seconds").replace("+00:00", "Z"),
        "unixtime": int(now.timestamp())
    }


# ---------------------------------------------------------
# Personaliza los headers HTTP
# ---------------------------------------------------------
@app.after_request
def customize_headers(response):

    # Oculta la versión de Werkzeug/Python
    response.headers["Server"] = "TimeBoard Time Service/1.0"

    return response


# ---------------------------------------------------------
# Página principal
# ---------------------------------------------------------
@app.route("/")
def index():

    return jsonify({
        "service": "TimeBoard Time Service",
        "short_name": "TBTS",
        "version": "1.0",
        "status": "online",
        "description": "Lightweight HTTP time service for legacy Palm OS devices.",
        "endpoints": {
            "utc": "/api/utc"
        }
    })


# ---------------------------------------------------------
# Devuelve la hora UTC
# ---------------------------------------------------------
@app.route("/api/utc")
def api_utc():

    now = datetime.now(timezone.utc)

    return jsonify(build_utc_response(now))


# ---------------------------------------------------------
# Main
# ---------------------------------------------------------
if __name__ == "__main__":
    app.run(host="0.0.0.0", port=80)