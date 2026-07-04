from flask import Flask, jsonify, request
from datetime import datetime, timezone

app = Flask(__name__)


# ---------------------------------------------------------
# Construye una respuesta compatible con WorldTimeAPI
# ---------------------------------------------------------
def build_worldtimeapi_response(now):

    now_utc = now.astimezone(timezone.utc)

    # UTC offset con formato ±HH:MM
    offset = now.strftime("%z")
    offset = offset[:3] + ":" + offset[3:]

    # Día del año
    day_of_year = now.timetuple().tm_yday

    # Lunes = 1 ... Domingo = 7
    day_of_week = now.isoweekday()

    # Semana ISO
    week_number = now.isocalendar().week

    # Offset en segundos
    raw_offset = int(now.utcoffset().total_seconds())

    # Horario de verano
    if now.dst() is None:
        dst = False
        dst_offset = 0
    else:
        dst_offset = int(now.dst().total_seconds())
        dst = (dst_offset != 0)

    response = {

        "abbreviation": str(now.tzname()),
        "client_ip": request.remote_addr,
        "datetime": now.isoformat(timespec="seconds"),
        "day_of_week": day_of_week,
        "day_of_year": day_of_year,
        "dst": dst,
        "dst_from": None,
        "dst_offset": dst_offset,
        "dst_until": None,
        "raw_offset": raw_offset,
        "timezone": str(now.tzinfo),
        "unixtime": int(now.timestamp()),
        "utc_datetime": now_utc.isoformat(timespec="seconds").replace("+00:00", "Z"),
        "utc_offset": offset,
        "week_number": week_number

    }

    return response


# ---------------------------------------------------------
# Devuelve la hora de la zona horaria local del servidor
# ---------------------------------------------------------
@app.route("/api/ip")
def api_ip():

    now = datetime.now().astimezone()

    return jsonify(build_worldtimeapi_response(now))

if __name__ == "__main__":
    app.run(host="0.0.0.0", port=80)