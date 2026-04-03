from models.ticket import Ticket

class ParkingLot:
    def __init__(self, spots, rate_policy):
        self._spots = spots
        self._rate_policy = rate_policy
        self._active_tickets = {}
        self._history_tickets = []
        self._total = 0

    def register_entry(self, vehicle):
        for spot in self._spots:
            if not spot.is_occupied and spot.is_compatible(vehicle):
                spot.assign()
                ticket = Ticket(vehicle, spot)
                self._active_tickets[ticket.id] = ticket
                return ticket

        raise Exception("No hay lugares disponibles compatibles")

    def register_exit(self, ticket_id, hours):
        if ticket_id not in self._active_tickets:
            raise Exception("Ticket no encontrado")

        ticket = self._active_tickets[ticket_id]

        cost = self._rate_policy.calculate(hours, ticket.vehicle)

        ticket.close(hours, cost)
        ticket.spot.release()

        del self._active_tickets[ticket_id]

        self._history_tickets.append(ticket)
        self._total += cost

        return ticket

    def get_active_tickets(self):
        return list(self._active_tickets.values())

    def get_history(self):
        return self._history_tickets
    
    def get_occupancy(self):
        occupied = sum(1 for s in self._spots if s.is_occupied)
        free = len(self._spots) - occupied
        return free, occupied
    
    def get_spots_status(self):
        return self._spots