from flask import Flask, render_template, request, redirect

from models.vehicle import Car, Motorcycle
from models.spot import ParkingSpot
from models.parking_lot import ParkingLot
from models.rates import VehicleRatePolicy

app = Flask(__name__)

# =============================
# INICIALIZACIÓN DEL MODELO
# =============================
spots = [
    # Universales
    ParkingSpot("U1", "Universal"),
    ParkingSpot("U2", "Universal"),
    ParkingSpot("U3", "Universal"),
    ParkingSpot("U4", "Universal"),

    # Autos
    ParkingSpot("C1", "Car"),
    ParkingSpot("C2", "Car"),
    ParkingSpot("C3", "Car"),

    # Motos
    ParkingSpot("M1", "Motorcycle"),
    ParkingSpot("M2", "Motorcycle"),
    ParkingSpot("M3", "Motorcycle"),
]

parking = ParkingLot(spots, VehicleRatePolicy())


def create_vehicle(vtype, plates):
    if vtype == "Car":
        return Car(plates)
    elif vtype == "Motorcycle":
        return Motorcycle(plates)
    else:
        raise Exception("Tipo inválido")


# =============================
# RUTAS (CONTROLLER)
# =============================

@app.route("/")
def dashboard():
    free, occupied = parking.get_occupancy()
    tickets = parking.get_active_tickets()
    history = parking.get_history()
    spots = parking.get_spots_status()

    return render_template(
        "dashboard.html",
        free=free,
        occupied=occupied,
        tickets=tickets,
        history=history,
        spots=spots
    )

@app.route("/entry", methods=["GET", "POST"])
def entry():
    if request.method == "POST":
        plates = request.form["plates"]
        vtype = request.form["type"]

        try:
            vehicle = create_vehicle(vtype, plates)
            parking.register_entry(vehicle)
        except Exception as e:
            return str(e)

        return redirect("/")

    return render_template("entry.html")


@app.route("/exit", methods=["GET", "POST"])
def exit():
    if request.method == "POST":
        ticket_id = int(request.form["ticket_id"])
        hours = int(request.form["hours"])

        try:
            ticket = parking.register_exit(ticket_id, hours)
        except Exception as e:
            return str(e)

        return render_template("exit_result.html", ticket=ticket)

    return render_template("exit.html")

if __name__ == "__main__":
    app.run(debug=True)