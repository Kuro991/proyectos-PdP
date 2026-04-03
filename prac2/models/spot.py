class ParkingSpot:
    def __init__(self, spot_id: str, allowed_type: str):
        self._id = spot_id
        self._allowed_type = allowed_type
        self._occupied = False

    @property
    def id(self):
        return self._id

    @property
    def allowed_type(self):
        return self._allowed_type

    @property
    def is_occupied(self):
        return self._occupied

    def is_compatible(self, vehicle):
        return (
            self._allowed_type == "Universal" or
            vehicle.get_type() == self._allowed_type
        )

    def assign(self):
        if self._occupied:
            raise Exception("El lugar ya está ocupado")
        self._occupied = True

    def release(self):
        if not self._occupied:
            raise Exception("El lugar ya está libre")
        self._occupied = False