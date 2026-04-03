from models.vehicle import Car, Motorcycle
from models.spot import ParkingSpot
from models.parking_lot import ParkingLot
from models.rates import VehicleRatePolicy


def create_vehicle(vtype, plates):
    if vtype == "Car":
        return Car(plates)
    elif vtype == "Motorcycle":
        return Motorcycle(plates)
    else:
        raise Exception("Tipo inválido")


def main():
    spots = [
        ParkingSpot("A1", "Car"),
        ParkingSpot("A2", "Car"),
        ParkingSpot("M1", "Motorcycle"),
        ParkingSpot("M2", "Motorcycle"),
    ]

    parking = ParkingLot(spots, VehicleRatePolicy())

    while True:
        print("\n1. Registrar entrada")
        print("2. Registrar salida")
        print("3. Ver ocupación")
        print("4. Ver tickets activos")
        print("5. Salir")

        option = input("Seleccione opción: ")

        try:
            if option == "1":
                plates = input("Placas: ")
                vtype = input("Tipo (Car/Motorcycle): ")

                vehicle = create_vehicle(vtype, plates)
                ticket = parking.register_entry(vehicle)

                print(f"Entrada: placas={plates} tipo={vtype} -> Ticket #{ticket.id}, spot={ticket.spot.id}")

            elif option == "2":
                tid = int(input("ID Ticket: "))
                hours = int(input("Horas: "))

                cost, ticket = parking.register_exit(tid, hours)

                print(f"Salida: ticket={tid} -> tiempo={hours}h costo=${cost} spot liberado={ticket.spot.id}")

            elif option == "3":
                free, occupied = parking.get_occupancy()
                print(f"Ocupación: libres={free} ocupados={occupied}")

            elif option == "4":
                print("Tickets activos:", parking.get_active_tickets())

            elif option == "5":
                break

            else:
                print("Opción inválida")

        except Exception as e:
            print("Error:", e)


if __name__ == "__main__":
    main()