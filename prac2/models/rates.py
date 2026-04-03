class RatePolicy:
    def calculate(self, hours, vehicle):
        raise NotImplementedError()


class VehicleRatePolicy(RatePolicy):
    def calculate(self, hours, vehicle):
        rate = self._get_rate(vehicle)
        return hours * rate

    def _get_rate(self, vehicle):
        # Polimorfismo por tipo de vehículo
        if vehicle.get_type() == "Car":
            return 20
        elif vehicle.get_type() == "Motorcycle":
            return 10
        else:
            raise Exception("Tipo de vehículo no soportado")