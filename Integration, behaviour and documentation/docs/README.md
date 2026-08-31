# EventFlow – Pretoria Innovation Expo 2026

## COS 214 Practical 3

EventFlow is a C++ project that demonstrates the use of the **Composite** and **Observer** design patterns.

The system is based on a fictional event called the **Pretoria Innovation Expo 2026**. The event consists of different halls, zones and operational units. A central event control system sends notifications to relevant parts of the event when changes occur.

---

## Team Members

| Student Number | Name                          |
| -------------- | ----------------------------- |
| u25128648      | **Boikemelo Masoka**          |
| u25208943      | **Boitumelo Ashley Monareng** |
| u25446968      | **Hluyo Terrence Vakai**      |

---

## Project Description

The project uses the **Composite Pattern** to represent the event as a hierarchy.

For example:

```text
Pretoria Innovation Expo
├── Tech Hall
│   ├── Future Mobility Zone
│   │   ├── Demo Stage
│   │   └── Innovation Booth
│   └── Information Desk
└── Community Hall
    ├── Shuttle Stop
    ├── Security Team
    └── Food Vendor
```

The **Observer Pattern** is used to notify event components about changes such as:

* Weather alerts
* Capacity alerts
* Schedule changes
* Transport delays
* Evacuation notices
* Pause and resume notices

Different event units can respond differently to the same notification.

---

## Team Responsibilities

### Boikemelo Masoka — u25128648

Responsible for the **Composite Pattern and event structure**.

Main areas:

* `EventComponent`
* `EventUnit`
* `EventGroup`
* Concrete event units
* Event hierarchy and ownership

---

### Boitumelo Ashley Monareng — u25208943

Responsible for the **Observer Pattern and notification system**.

Main areas:

* `Observer`
* `Subject`
* `EventControl`
* `Notice`
* Observer registration
* Cascading notifications

---

### Hluyo Terrence Vakai — u25446968

Responsible for **integration, UML and documentation**.

Main areas:

* `main.cpp`
* `Makefile`
* `Doxyfile`
* `README.md`
* `report.md`
* Sequence diagrams
* Final testing and integration

---

## Building the Project

Compile the project using:

```bash
make
```

---

## Running the Project

After compiling, run:

```bash
./eventflow
```

---

## Documentation

The project includes:

* A UML class diagram
* An object diagram
* Four sequence diagrams
* Doxygen documentation
* A design report

To generate Doxygen documentation:

```bash
doxygen Doxyfile
```

---

## Design Patterns Used

### Composite Pattern

Used to represent the event hierarchy and allow individual event units and groups of units to be treated uniformly.

### Observer Pattern

Used to allow `EventControl` and event groups to notify registered components when an event-related change occurs.

