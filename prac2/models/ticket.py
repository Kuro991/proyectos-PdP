from datetime import datetime


class Ticket:
    _counter = 1

    def __init__(self, vehicle, spot):
        self._id = Ticket._counter
        Ticket._counter += 1

        self._vehicle = vehicle
        self._spot = spot
        self._entry_time = datetime.now()
        self._exit_time = None
        self._active = True
        self._cost = 0
        self._hours = 0

    @property
    def id(self):
        return self._id

    @property
    def vehicle(self):
        return self._vehicle

    @property
    def spot(self):
        return self._spot

    @property
    def active(self):
        return self._active

    @property
    def cost(self):
        return self._cost

    @property
    def hours(self):
        return self._hours

    def close(self, hours, cost):
        if not self._active:
            raise Exception("El ticket ya está cerrado")

        self._exit_time = datetime.now()
        self._active = False
        self._hours = hours
        self._cost = cost