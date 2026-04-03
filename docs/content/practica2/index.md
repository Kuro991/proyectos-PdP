+++
date = '2026-04-02T00:00:00-08:00'
draft = false
title = 'Practica 2: Programacion orientada a objetos. Simulador de estacionamiento'
+++

# Práctica 02: Simulador de Estacionamiento

# Subsecciones
- Reporte
    - Introduccion
    - Modelo del dominio
        - Diagrama UML
        - Clases y responsabilidades
    - Evidencia de conceptos
        - Encapsulacion
        - Abstraccion
        - Composicion
        - Herencia/subtipos
        - Polimorfismo
    - MVC con Flask
    - Pruebas manuales
        - Flujo 1: Entrada y salida de automovil
        - Flujo 2: Compatibilidad de espacios
    - Preguntas guias
    - Conclusiones
    - Referencias

- Sesiones:
    - Sesion 1
    - Sesion 2
    - Sesion 3


## 1. Introducción

En esta práctica se desarrolló un simulador de estacionamiento utilizando el paradigma de Programación Orientada a Objetos (POO). El sistema permite gestionar la entrada y salida de vehículos, asignación de espacios, cálculo de tarifas y visualización del estado del estacionamiento.

El objetivo principal fue aplicar conceptos fundamentales de POO como encapsulación, abstracción, herencia, composición y polimorfismo, culminando con la implementación de una interfaz web utilizando Flask bajo una arquitectura MVC simple.

---

## 2. Modelo del dominio

### 2.1 Diagrama UML (descripción)

El sistema está compuesto por las siguientes entidades principales:

- Vehicle (clase base)
- Car y Motorcycle (subclases)
- ParkingSpot
- Ticket
- ParkingLot
- RatePolicy

Relaciones:
- ParkingLot contiene múltiples ParkingSpot (composición)
- ParkingLot administra Ticket
- Ticket tiene relación con Vehicle y ParkingSpot
- RatePolicy es utilizada por ParkingLot

![Diagrama UML](/docs/content/practica2/images/DiagramaUML.png)


---

### 2.2 Clases y responsabilidades

**Vehicle**
- Representa un vehículo genérico
- Define interfaz común (`get_type`)

**Car / Motorcycle**
- Subtipos de Vehicle
- Representan tipos específicos de vehículos

**ParkingSpot**
- Representa un espacio de estacionamiento
- Controla si está ocupado o libre
- Define compatibilidad con tipos de vehículo

**Ticket**
- Representa la estancia de un vehículo
- Guarda tiempos, costo y estado

**ParkingLot**
- Clase principal del sistema
- Administra espacios, tickets activos e historial
- Asigna lugares y procesa salidas

**RatePolicy**
- Define la lógica de cálculo de tarifas
- Permite cambiar reglas sin modificar el sistema principal

---

## 3. Evidencia de conceptos POO

### 3.1 Encapsulación

```python
def assign(self):
    if self._occupied:
        raise Exception("El lugar ya está ocupado")
    self._occupied = True
```
La encapsulación consiste en ocultar el estado interno de un objeto y permitir su modificación únicamente a través de métodos controlados. En este caso, el atributo `_occupied` no se modifica directamente desde el exterior, sino mediante el método `assign()`.

Este método valida una condición crítica del sistema: evitar que un mismo espacio sea ocupado por más de un vehículo al mismo tiempo. Si el espacio ya está ocupado, se lanza una excepción, protegiendo así la integridad del estado del sistema.

### 3.2 Abstracción

```python
class RatePolicy:
    def calculate(self, hours, vehicle):
        raise NotImplementedError()
```

La abstracción permite definir comportamientos generales sin especificar su implementación concreta. En este caso, `RatePolicy` define una interfaz común para el cálculo de tarifas.

Esto permite desacoplar la lógica de cobro del resto del sistema, de modo que se puedan implementar diferentes políticas de tarifas sin modificar las clases principales como `ParkingLot`.

### 3.3 Composición

```python
class ParkingLot:
    def __init__(self, spots, rate_policy):
        self._spots = spots
        self._active_tickets = {}
```

La composición se refiere a la relación donde una clase contiene instancias de otras clases. Aquí, `ParkingLot` administra una colección de `ParkingSpot` y `Ticket`.

Esto permite que el estacionamiento controle directamente los espacios disponibles y los tickets activos, centralizando la lógica del sistema y facilitando su gestión.

### 3.4 Herencia / Subtipos

```python
class Car(Vehicle):
    def get_type(self):
        return "Car"

class Motorcycle(Vehicle):
    def get_type(self):
        return "Motorcycle"
```

La herencia permite crear nuevas clases basadas en una clase existente. En este caso, `Car` y `Motorcycle` heredan de `Vehicle`, reutilizando su estructura y comportamiento.

Esto facilita la extensión del sistema sin duplicar código, permitiendo agregar nuevos tipos de vehículos en el futuro.

### 3.5 Polimorfismo

```python
def calculate(self, hours, vehicle):
    if vehicle.get_type() == "Car":
        return hours * 20
    elif vehicle.get_type() == "Motorcycle":
        return hours * 10
```

El polimorfismo permite que diferentes objetos respondan de manera distinta a una misma operación. En este caso, el método `calculate()` aplica tarifas distintas dependiendo del tipo de vehículo.

Esto aporta flexibilidad al sistema, ya que permite modificar o extender el comportamiento sin cambiar la estructura general del programa.

El uso combinado de estos principios permite cumplir con el principio de responsabilidad única (SRP) y facilita la extensibilidad del sistema.

---

## 4. MVC con Flask

**Model**

- Se encuentra en la carpeta `models/`
- Contiene toda la logica del sistema

**View**
- Archivos HTML en `templates/`
- Presentan la informaicon al usuario

**Controller**
- Archivo `app.py`
- Maneja turas y conecta modelo con vistas

**Rutas implementadas**
- `/` → Dashboard
- `/entry` → Registro de entrada
- `/exit` → Registro de salida

**Pantallas**

1. Dashboard
    - Muestra ocupacion
    - Tickets activos
    - Historial
    - Estado de espacios
2. Entrada
    - Formulario para registrar vehiculos
3. Salida
    - Formulario para registrar salida
    - Muestra costo y tiempo

---

## 5. Pruebas manuales

### 5.1 Flujo 1: Entrada y salida del automovil

1. Registrar vehiculo tipo car
![entrada car](/docs/content/practica2/images/entradacar.png)
2. Se asigna un espacio compatible

![espacio asignado](/docs/content/practica2/images/espacioasignado.png)

3. Registrar salida con 2 horas

![registrarsalida](/docs/content/practica2/images/registrarsalida.png)

4. Resultado
    - Costo correcto ($40)
    - Espacio liberado
    - Ticket pasa a historial

![salida](/docs/content/practica2/images/salida.png)


### 5.2 Flujo 2: Compatibilidad de espacios:

1. Intentar ingresar motocicleta en espacio de auto

![entrada moto](/docs/content/practica2/images/entradamoto.png)

2. Sistema asigna espacio compatible automaticamente

![entrada moto 2](/docs/content/practica2/images/entradamoto2.png)

3. Si no hay espacios disponibles:
    - Se muestra error

![error](/docs/content/practica2/images/error.png)


---

## 6. Preguntas guia

**1. ¿Qué clase concentra la responsabilidad de asignar spots y por qué?**

La clase ParkingLot es responsable de asignar espacios, ya que centraliza la lógica del sistema y tiene acceso a todos los espacios disponibles y su estado.

**2. ¿Qué invariantes protege tu modelo?**

- Un espacio no puede estar ocupado por más de un vehículo
- Un ticket activo representa un vehículo dentro del sistema
- No se puede cerrar un ticket que ya fue cerrado

**3. ¿Dónde se aplica polimorfismo y qué ventaja aporta?**

Se aplica en RatePolicy al calcular tarifas dependiendo del tipo de vehículo. Esto permite extender el sistema sin modificar código existente, facilitando mantenimiento y escalabilidad.

**4. ¿Qué parte del sistema pertenece a Model, View y Controller?**

- Model: clases en models/
- View: plantillas HTML
- Controller: rutas en app.py

**5. Si mañana cambian las tarifas, ¿qué clase(es) tocarías y por qué?**

Solo se modificaría la clase RatePolicy, ya que encapsula la lógica de cobro, evitando afectar otras partes del sistema.

---

## 7. Conclusiones

El desarrollo del simulador permitió aplicar de manera práctica los conceptos fundamentales de POO. Se logró un diseño modular, extensible y mantenible gracias al uso de abstracción y separación de responsabilidades.

La implementación de Flask permitió integrar el modelo en una interfaz web funcional, respetando el patrón MVC. Además, la incorporación de historial y visualización de espacios mejora la experiencia del usuario y la trazabilidad del sistema.

## 8. Referencias

Pallets Projects. “Welcome to Flask — Flask Documentation (3.1.x).” Accedido: 2026-03-12. (2026), direc-
ción: https://flask.palletsprojects.com/ (visitado 12-03-2026).

Python Software Foundation. “dataclasses — Data Classes.” Accedido: 2026-03-12. (2026), dirección:
https://docs.python.org/3/library/dataclasses.html (visitado 12-03-2026).

M. Fowler. “Inversion of Control Containers and the Dependency Injection pattern.” Accedido: 2026-
03-12. (2004), dirección: https : / / martinfowler . com / articles / injection . html (visitado
12-03-2026).

Python Typing Team. “Protocols — typing specification.” Accedido: 2026-03-12. (2026), dirección: https:
//typing.python.org/en/latest/spec/protocol.html (visitado 12-03-2026).

Pallets Projects. “Quickstart — Flask Documentation (3.1.x).” Accedido: 2026-03-12. (2026), dirección:
https://flask.palletsprojects.com/en/stable/quickstart/ (visitado 12-03-2026).

Flask-es Read the Docs. “Plantillas — Documentación de Flask (Tutorial).” Accedido: 2026-03-12. (2026),
dirección: https://flask-es.readthedocs.io/tutorial/templates/ (visitado 12-03-2026)

# Sesiones

## Sesion 1

### parking_lot.py

```python
from models.ticket import Ticket


class ParkingLot:
    def __init__(self, spots, rate_policy):
        self._spots = spots
        self._rate_policy = rate_policy
        self._active_tickets = {}
        self._total = 0

    def register_entry(self, vehicle):
        # buscar lugar disponible compatible
        for spot in self._spots:
            if not spot.is_occupied and spot.allowed_type == vehicle.type:
                spot.assign()
                ticket = Ticket(vehicle, spot)
                self._active_tickets[ticket.id] = ticket

                return ticket

        raise Exception("No hay lugares disponibles")

    def register_exit(self, ticket_id, hours):
        if ticket_id not in self._active_tickets:
            raise Exception("Ticket no encontrado")

        ticket = self._active_tickets[ticket_id]

        ticket.close()
        cost = self._rate_policy.calculate(hours, ticket.vehicle)

        ticket.spot.release()

        del self._active_tickets[ticket_id]
        self._total += cost

        return cost, ticket

    def get_occupancy(self):
        occupied = sum(1 for s in self._spots if s.is_occupied)
        free = len(self._spots) - occupied
        return free, occupied

    def get_active_tickets(self):
        return list(self._active_tickets.keys())
```

### rates.py

```python
class RatePolicy:
    def calculate(self, hours, vehicle):
        raise NotImplementedError("Debe implementar calculate()")


class SimpleRatePolicy(RatePolicy):
    def calculate(self, hours, vehicle):
        return hours * 20
```

### spot.py

```python
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

    def assign(self):
        if self._occupied:
            raise Exception("El lugar ya está ocupado")
        self._occupied = True

    def release(self):
        if not self._occupied:
            raise Exception("El lugar ya está libre")
        self._occupied = False
```

### ticket.py
```python
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

    def close(self):
        if not self._active:
            raise Exception("El ticket ya está cerrado")

        self._exit_time = datetime.now()
        self._active = False

    def get_hours(self):
        if not self._exit_time:
            raise Exception("El ticket sigue activo")

        delta = self._exit_time - self._entry_time
        return max(1, int(delta.total_seconds() // 3600))
```

### vehicle.py

```python
class Vehicle:
    def __init__(self, plates: str, vehicle_type: str):
        if not plates:
            raise ValueError("Las placas no pueden estar vacías")

        self._plates = plates
        self._type = vehicle_type

    @property
    def plates(self):
        return self._plates

    @property
    def type(self):
        return self._type

    def __str__(self):
        return f"{self._type} ({self._plates})"
```

### cli.py

```python
from models.vehicle import Vehicle
from models.spot import ParkingSpot
from models.parking_lot import ParkingLot
from models.rates import SimpleRatePolicy


def main():
    # crear lugares
    spots = [
        ParkingSpot("A1", "Car"),
        ParkingSpot("A2", "Car"),
        ParkingSpot("M1", "Motorcycle"),
        ParkingSpot("M2", "Motorcycle"),
    ]

    parking = ParkingLot(spots, SimpleRatePolicy())

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

                vehicle = Vehicle(plates, vtype)
                ticket = parking.register_entry(vehicle)

                print(f"Ticket #{ticket.id}, spot={ticket.spot.id}")

            elif option == "2":
                tid = int(input("ID Ticket: "))
                hours = int(input("Horas: "))

                cost, ticket = parking.register_exit(tid, hours)

                print(f"Costo=${cost}, spot liberado={ticket.spot.id}")

            elif option == "3":
                free, occupied = parking.get_occupancy()
                print(f"Libres={free}, Ocupados={occupied}")

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
```

## Sesion 2

### parking_lot

```
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
```

### rates.py

```python
class RatePolicy:
    def calculate(self, hours, vehicle):
        raise NotImplementedError()


class VehicleRatePolicy(RatePolicy):
    def calculate(self, hours, vehicle):
        rate = self._get_rate(vehicle)
        return hours * rate

    def _get_rate(self, vehicle):
        if vehicle.get_type() == "Car":
            return 20
        elif vehicle.get_type() == "Motorcycle":
            return 10
        else:
            raise Exception("Tipo de vehículo no soportado")
```

### spot.py

```python
class ParkingSpot:
    def __init__(self, spot_id: str, allowed_type: str):
        self._id = spot_id
        self._allowed_type = allowed_type
        self._occupied = False

    @property
    def id(self):
        return self._id

    def is_compatible(self, vehicle):
        return vehicle.get_type() == self._allowed_type

    @property
    def is_occupied(self):
        return self._occupied

    def assign(self):
        if self._occupied:
            raise Exception("El lugar ya está ocupado")
        self._occupied = True

    def release(self):
        if not self._occupied:
            raise Exception("El lugar ya está libre")
        self._occupied = False
```

### ticket.py

```python
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
```

### vehicle.py

```python
class Vehicle:
    def __init__(self, plates: str):
        if not plates:
            raise ValueError("Las placas no pueden estar vacías")

        self._plates = plates

    @property
    def plates(self):
        return self._plates

    def get_type(self):
        raise NotImplementedError()


class Car(Vehicle):
    def get_type(self):
        return "Car"


class Motorcycle(Vehicle):
    def get_type(self):
        return "Motorcycle"
```

### cli.py

```python
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
```

## Sesion 3

### app.py

```python
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
    ParkingSpot("A1", "Car"),
    ParkingSpot("A2", "Car"),
    ParkingSpot("M1", "Motorcycle"),
    ParkingSpot("M2", "Motorcycle"),
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

    return render_template(
        "dashboard.html",
        free=free,
        occupied=occupied,
        tickets=tickets
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
            parking.register_exit(ticket_id, hours)
        except Exception as e:
            return str(e)

        return redirect("/")

    return render_template("exit.html")


if __name__ == "__main__":
    app.run(debug=True)
```

### base.html

```html
<!DOCTYPE html>
<html>
<head>
    <title>Parking Lot</title>
    <link rel="stylesheet" href="{{ url_for('static', filename='styles.css') }}">
</head>
<body>
    <h1>Simulador de Estacionamiento</h1>

    <nav>
        <a href="/">Dashboard</a> |
        <a href="/entry">Registrar Entrada</a> |
        <a href="/exit">Registrar Salida</a>
    </nav>

    <hr>

    {% block content %}
    {% endblock %}
</body>
</html>
```

### dashboard.html

```html
{% extends "base.html" %}

{% block content %}
<h2>Dashboard</h2>

<p><b>Libres:</b> {{ free }}</p>
<p><b>Ocupados:</b> {{ occupied }}</p>

<h3>Tickets Activos</h3>
<ul>
{% for t in tickets %}
    <li>
        Ticket #{{ t.id }} |
        {{ t.vehicle.plates }} |
        {{ t.vehicle.get_type() }} |
        Spot {{ t.spot.id }}
    </li>
{% else %}
    <li>No hay tickets activos</li>
{% endfor %}
</ul>

<hr>

<h3>Mapa del Estacionamiento</h3>

<table border="1" cellpadding="10">
<tr>
    <th>ID</th>
    <th>Tipo</th>
    <th>Estado</th>
</tr>

{% for s in spots %}
<tr>
    <td>{{ s.id }}</td>
    <td>{{ s.allowed_type }}</td>
    <td class="{% if s.is_occupied %}ocupado{% else %}libre{% endif %}">
        {% if s.is_occupied %}
            🔴 Ocupado
        {% else %}
            🟢 Libre
        {% endif %}
    </td>
</tr>
{% endfor %}
</table>


<h3>Historial</h3>
<ul>
{% for t in history %}
    <li>
        Ticket #{{ t.id }} - {{ t.vehicle.plates }}        
        {{ t.vehicle.plates }} |
        {{ t.vehicle.get_type() }} |
        Tiempo: {{ t.hours }}h |
        Costo: ${{ t.cost }}
    </li>
{% else %}
    <li>No hay historial</li>
{% endfor %}
</ul>
{% endblock %}
```

### entry.html

```html
{% extends "base.html" %}

{% block content %}
<h2>Registrar Entrada</h2>

<form method="POST">
    <label>Placas:</label>
    <input type="text" name="plates" required><br><br>

    <label>Tipo:</label>
    <select name="type">
        <option value="Car">Car</option>
        <option value="Motorcycle">Motorcycle</option>
    </select><br><br>

    <button type="submit">Registrar</button>
</form>
{% endblock %}
```

### exit.html

```html
{% extends "base.html" %}

{% block content %}
<h2>Registrar Salida</h2>

<form method="POST">
    <label>ID Ticket:</label>
    <input type="number" name="ticket_id" required><br><br>

    <label>Horas:</label>
    <input type="number" name="hours" required><br><br>

    <button type="submit">Registrar salida</button>
</form>
{% endblock %}
```

### exit_result.html

```html
{% extends "base.html" %}

{% block content %}
<h2>Salida registrada</h2>

<p><b>Ticket:</b> #{{ ticket.id }}</p>
<p><b>Vehículo:</b> {{ ticket.vehicle.plates }}</p>
<p><b>Tipo:</b> {{ ticket.vehicle.get_type() }}</p>
<p><b>Tiempo:</b> {{ ticket.hours }} horas</p>
<p><b>Costo:</b> ${{ ticket.cost }}</p>
<p><b>Spot liberado:</b> {{ ticket.spot.id }}</p>

<a href="/">Volver al dashboard</a>
{% endblock %}
```

### styles.css

```css
body {
    font-family: Arial;
    margin: 20px;
}

table {
    border-collapse: collapse;
}

td, th {
    padding: 10px;
    text-align: center;
}

.libre {
    background-color: #c8f7c5;
}

.ocupado {
    background-color: #f7c5c5;
}
```