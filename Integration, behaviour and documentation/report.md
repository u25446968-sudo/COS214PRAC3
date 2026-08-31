# COS 214 Practical 3 --- EventFlow Design Report

## Pretoria Innovation Expo 2026

### Team Members

  -----------------------------------------------------------------------
  Member                  Name                    Primary Responsibility
  ----------------------- ----------------------- -----------------------
  Member 1                **Kemi**                Composite / Event
                                                  Structure

  Member 2                **Boitumelo Ashley      Observer / Notification
                          Monareng**              System

  Member 3                **Hluyo Terrence        Integration, UML and
                          Vakai**                 Documentation
  -----------------------------------------------------------------------

------------------------------------------------------------------------

## 1. Event Name and Concept

### Pretoria Innovation Expo 2026

Pretoria Innovation Expo 2026 is a fictional live technology and
innovation exhibition designed as the domain for the EventFlow
coordination engine. The expo brings together technology demonstrations,
innovation booths, visitor services, transport services and security
operations.

The event is modelled as a hierarchy because an organiser should be able
to reason about the whole expo, a hall, a zone or an individual
operational unit through the same `EventComponent` interface.

The sample event tree is:

``` text
Pretoria Innovation Expo (root Composite)
├── Tech Hall (Composite)
│   ├── Future Mobility Zone (Composite)
│   │   ├── Keynote Stage (Leaf)
│   │   └── Robotics Demo Booth (Leaf)
│   ├── Digital Futures Zone (Composite)
│   │   ├── AI Lab Booth (Leaf)
│   │   └── Visitor Information Desk (Leaf)
│   └── Future Bites Vendor (Leaf; moved here during execution)
└── Community Hall (Composite)
    ├── Innovation Shuttle Stop (Leaf)
    └── Tech Hall Security (Leaf)
```

The system also responds to changes while the expo is running. A central
`EventControl` component can issue notices such as weather alerts,
capacity warnings, schedule changes, transport delays, evacuation
instructions, pauses and resumptions.

Different operational units react differently to the same notice. For
example:

-   A `DemoStage` may pause during a weather alert.
-   A `SecurityTeam` may increase monitoring during a capacity alert.
-   A `ShuttleStop` may update its transport status during a delay.
-   An `InformationDesk` may remain operational to provide visitor
    guidance during an emergency.

The central architectural idea is:

> **Composite answers what is contained inside an event area, while
> Observer answers who needs to hear about a change.**

------------------------------------------------------------------------

## 2. GoF Participant Mapping

### 2.1 Composite Pattern

  -----------------------------------------------------------------------
  GoF Role                EventFlow Class         Responsibility
  ----------------------- ----------------------- -----------------------
  Component               `EventComponent`        Provides common
                                                  operations such as
                                                  `open()`, `close()`,
                                                  `reportStatus()` and
                                                  `getCapacity()`.

  Composite               `EventGroup`            Owns child
                                                  `EventComponent`
                                                  objects and recursively
                                                  performs common
                                                  operations.

  Leaf                    `EventUnit` and         Represents individual
                          concrete event units    operational units with
                                                  specialised behaviour.

  Client                  `main.cpp`              Builds and uses the
                                                  event structure through
                                                  the common interface.
  -----------------------------------------------------------------------

### 2.2 Observer Pattern

  -----------------------------------------------------------------------
  GoF Role                EventFlow Class         Responsibility
  ----------------------- ----------------------- -----------------------
  Subject                 `Subject`               Defines observer
                                                  registration and
                                                  notification behaviour.

  Concrete Subject        `EventControl` and      Publishes notices.
                          `EventGroup`            

  Observer                `Observer`              Defines the
                                                  notification interface.

  Concrete Observers      `EventGroup` and        React polymorphically
                          concrete event units    to notices.
  -----------------------------------------------------------------------

`EventGroup` participates in more than one collaboration. Structurally
it is a Composite, but it can also receive notifications as an Observer
and cascade notifications as a Subject. These are separate
responsibilities and do not represent misuse of either pattern.

------------------------------------------------------------------------

## 3. Architecture and Design Rationale

### 3.1 Genuine Part-Whole Structure

The Expo is a genuine Composite tree. A hall contains zones and
operational units, while a zone can contain further groups and leaves.

All event components support common operations:

``` cpp
open();
close();
reportStatus();
getCapacity();
```

This means a client can interact with either one leaf or an entire
Composite through the same `EventComponent` interface.

### 3.2 Why Observer Is Required

`EventControl` should not contain hard-coded calls to every concrete
event unit. Doing so would make the controller dependent on the complete
event topology.

Observer allows interested components to register at runtime. It also
allows an `EventGroup` to receive a notice from above and publish it to
observers below.

### 3.3 Ownership Policy

Each `EventGroup` owns its direct children.

-   `add()` transfers ownership to the group.
-   `remove()` removes the child without deleting it and transfers
    ownership back to the caller.
-   The root Composite recursively destroys its owned subtree.

This makes runtime movement possible without double deletion.

### 3.4 Observer Ownership

Subjects do **not** own their observers.

Observer registrations are non-owning pointers because the Composite
tree already defines the ownership of event components. Observation is a
separate relationship.

The registration policy is:

-   `attach(nullptr)` is ignored.
-   Duplicate `attach()` calls do not create duplicate registrations.
-   `detach(nullptr)` is ignored.
-   Detaching an observer that is not registered is a safe no-op.
-   Notification uses a snapshot of the observer list so registration
    changes during notification do not invalidate the iteration.

### 3.5 Push Observer Choice

EventFlow uses the **Push Observer approach**.

The notification operation is conceptually:

``` cpp
update(const Notice& notice);
```

The notice contains relevant information such as:

-   notice type;
-   message;
-   associated value, where applicable.

Push was selected because event information such as capacity values and
safety messages is already available when the notice is published. This
makes the notification interaction explicit and avoids requiring every
observer to query the subject again.

------------------------------------------------------------------------

# 4. Team Responsibilities

## 4.1 Member 1 --- Kemi

### Primary Role

**Composite / Event Structure Lead**

### Objective

Kemi is responsible for implementing the structural side of EventFlow.
The objective is to represent the Pretoria Innovation Expo as a genuine
part-whole tree where individual event units and complete event groups
can be treated uniformly.

### Primary Files

``` text
EventComponent.h
EventComponent.cpp
EventUnit.h
EventUnit.cpp
EventGroup.h
EventGroup.cpp
```

### Concrete Event Unit Files

``` text
DemoStage.h / DemoStage.cpp
InnovationBooth.h / InnovationBooth.cpp
InformationDesk.h / InformationDesk.cpp
ShuttleStop.h / ShuttleStop.cpp
SecurityTeam.h / SecurityTeam.cpp
FoodVendor.h / FoodVendor.cpp
```

### Diagram Responsibilities

``` text
docs/object_diagram.puml
Composite-related section of docs/class_diagram.puml
```

### Tasks

1.  Implement `EventComponent` as the common Component abstraction.
2.  Ensure every polymorphic base class has a virtual destructor.
3.  Implement the common event operations:
    -   `open()`
    -   `close()`
    -   `reportStatus()`
    -   `getCapacity()`
4.  Implement `EventUnit` as the common base for individual operational
    units.
5.  Implement the concrete event unit classes.
6.  Ensure concrete leaves have genuinely different behaviour.
7.  Implement `EventGroup` as the Composite.
8.  Implement `add()` and a suitable `remove()` operation.
9.  Recursively implement the common operations through the Composite
    tree.
10. Build the nested Pretoria Innovation Expo event structure.
11. Define clear ownership and transfer rules.
12. Produce the Composite part of the UML class diagram.
13. Produce the Composite object diagram.

### Key Objective to Demonstrate

A client must be able to invoke behaviour through `EventComponent`
without knowing whether the object is a single event unit or an entire
group.

### Suggested Git Contributions

-   Create EventComponent abstraction
-   Implement EventUnit hierarchy
-   Add concrete expo event units
-   Implement EventGroup Composite
-   Add recursive Composite operations
-   Implement ownership and transfer rules
-   Build nested Expo structure

------------------------------------------------------------------------

## 4.2 Member 2 --- Boitumelo Ashley Monareng

### Primary Role

**Observer / Notification System Lead**

### Objective

Boitumelo Ashley Monareng is responsible for implementing the runtime
communication mechanism. The goal is to allow `EventControl` and event
areas to notify interested components without hard-coded calls to
concrete classes.

### Primary Files

``` text
Observer.h
Observer.cpp
Subject.h
Subject.cpp
EventControl.h
EventControl.cpp
Notice.h
Notice.cpp
```

### Additional Responsibilities

``` text
Observer/update implementations in concrete EventUnit classes
Observer/Subject-related EventGroup behaviour
Observer-related section of docs/class_diagram.puml
Observer/notification portions of docs/report.md
```

### Tasks

1.  Implement the `Observer` abstraction.
2.  Implement `update(...)`.
3.  Implement the `Subject` abstraction.
4.  Implement:
    -   `attach()`
    -   `detach()`
    -   `notify()`
5.  Implement `EventControl` as the central concrete subject.
6.  Implement the `Notice` representation.
7.  Implement at least six event notice types.

The system includes:

``` text
OPEN
CLOSE
SCHEDULE_CHANGE
CAPACITY_ALERT
WEATHER_ALERT
TRANSPORT_DELAY
EVACUATE
PAUSE
RESUME
STOCK_ALERT
```

8.  Prevent duplicate observer registrations.
9.  Safely handle attempts to detach observers that are not registered.
10. Maintain non-owning observer references.
11. Ensure registration changes during notification are safe.
12. Implement `EventGroup` as both an Observer and Subject where
    required.
13. Implement notification cascading through multiple event levels.
14. Implement meaningful concrete reactions to notices.
15. Document the Push Observer choice and transferred notice
    information.

### Cascading Scenario

A typical cascade is:

``` text
EventControl
    ↓ WEATHER_ALERT
Pretoria Innovation Expo
    ↓
Tech Hall
    ↓
Future Mobility Zone
    ↓
DemoStage
```

The `DemoStage` can pause its performance, while other concrete
observers react according to their own polymorphic behaviour.

### Suggested Git Contributions

-   Implement Observer interface
-   Implement Subject registration
-   Add duplicate attach and safe detach policy
-   Implement Notice representation
-   Add EventControl notification behaviour
-   Implement cascading notifications
-   Add concrete observer reactions

------------------------------------------------------------------------

## 4.3 Member 3 --- Hluyo Terrence Vakai

### Primary Role

**Integration, UML and Documentation Lead**

### Objective

Hluyo Terrence Vakai is responsible for integrating the Composite and
Observer implementations into a coherent executable and ensuring that
the code, UML diagrams, Doxygen documentation and demonstration all
describe the same design.

### Primary Files

``` text
main.cpp
Makefile
Doxyfile
README.md
docs/report.md
```

### Sequence Diagram Files

``` text
docs/SD1_build_register.puml
docs/SD2_cascading_notification.puml
docs/SD3_conditional_capacity.puml
docs/SD4_signature_safety_recovery.puml
```

### Tasks

1.  Build and maintain `main.cpp` as the complete EventFlow simulation.
2.  Integrate Kemi's Composite implementation with Boitumelo Ashley
    Monareng's Observer implementation.
3.  Construct the nested event structure.
4.  Register observers at runtime.
5.  Demonstrate at least three different notices.
6.  Demonstrate a cascading notification.
7.  Demonstrate observer registration changes.
8.  Demonstrate Composite traversal and capacity/status queries.
9.  Demonstrate runtime reorganisation.

A typical reorganisation is moving `Future Bites Vendor`:

``` text
Community Hall
      ↓ remove + detach
Future Bites Vendor
      ↓ add + attach
Tech Hall
```

10. Demonstrate at least five event rules with different polymorphic
    reactions.
11. Implement or integrate a condition-based decision such as a capacity
    threshold.
12. Create SD1 --- Building and registering part of the event.
13. Create SD2 --- Cascading event notification using a `loop` fragment.
14. Create SD3 --- Conditional event response using `alt` and `opt`.
15. Create SD4 --- Signature safety/recovery scenario.
16. Integrate the complete UML class diagram.
17. Configure and verify Doxygen.
18. Maintain the README with build, run, architecture and Doxygen
    instructions.
19. Test the complete system using `make`.
20. Verify that sequence-diagram messages correspond to real C++
    operations.

### Signature Scenario

The signature scenario can be an emergency evacuation followed by
recovery:

``` text
EventControl
      ↓ EVACUATE
Event Groups
      ↓
SecurityTeam → emergency response
DemoStage → pauses
InformationDesk → visitor guidance
ShuttleStop → transport support
      ↓
Registration / runtime change
      ↓
EventControl
      ↓ RESUME
Event returns to normal operation
```

### Suggested Git Contributions

-   Create main.cpp integration scenario
-   Add runtime event rules
-   Add runtime component transfer demonstration
-   Create SD1 building and registration
-   Create SD2 cascading notification
-   Create SD3 conditional response
-   Create SD4 signature scenario
-   Configure Doxygen and README
-   Final integration and demonstration cleanup

------------------------------------------------------------------------

# 5. Event Rules and Dynamic Behaviour

The system uses polymorphism so different concrete event units react
differently to notices.

1.  **Weather Alert:** `DemoStage` pauses its outdoor performance while
    `InformationDesk` remains active to provide guidance.
2.  **Capacity Alert:** `InnovationBooth` limits queue intake while
    `SecurityTeam` increases crowd-control readiness.
3.  **Transport Delay:** `ShuttleStop` changes its operational status
    and passenger messaging.
4.  **Evacuation:** `SecurityTeam` coordinates safety, `FoodVendor`
    secures equipment, `DemoStage` stops activity and `InformationDesk`
    provides evacuation guidance.
5.  **Schedule Change:** Different units update their own operational
    information.
6.  **Resume:** Paused components return to normal operation while
    respecting current observer registrations.

------------------------------------------------------------------------

# 6. Runtime Reorganisation

`Future Bites Vendor` initially belongs to `Community Hall`.

During runtime:

``` text
1. Remove vendor from Community Hall ownership.
2. Detach vendor from Community Hall notifications.
3. Add vendor to Tech Hall ownership.
4. Attach vendor to Tech Hall notifications.
```

The ownership relationship and Observer relationship are managed
separately.

No object is deleted during transfer.

------------------------------------------------------------------------

# 7. Sequence Diagram Portfolio

## SD1 --- Building and Registering

Shows:

-   client creation of the root Composite;
-   creation of nested Composites;
-   creation of at least two leaves;
-   ownership through `add()`;
-   Observer registrations.

The diagram distinguishes Composite ownership from Observer
registration.

## SD2 --- Cascading Event Notification

Shows:

-   `EventControl` publishing a notice;
-   notification through multiple Composite levels;
-   a `loop` fragment for notifying observers;
-   Push Observer information being passed through
    `update(const Notice&)`;
-   different concrete units reacting meaningfully.

## SD3 --- Conditional Event Response

Shows:

-   a Composite capacity operation;
-   an `alt` fragment for a capacity threshold;
-   an `opt` fragment for an additional response;
-   polymorphic reactions rather than type checking.

## SD4 --- Signature Event Scenario

Shows:

-   at least six lifelines;
-   at least two Composite levels;
-   Observer notification;
-   a runtime change such as detach/attach or component transfer;
-   a combined fragment;
-   safety response followed by recovery.

------------------------------------------------------------------------

# 8. Doxygen

The project contains a `Doxyfile` that generates browsable
documentation.

Public classes and operations are documented using Doxygen comments.

Important design decisions documented include:

1.  Observer references are non-owning.
2.  Composite `remove()` transfers ownership rather than deleting the
    object.
3.  Notification uses a snapshot of registrations to safely handle
    registration changes during notification.

------------------------------------------------------------------------

# 9. Git and GitHub Workflow Reflection

The team uses GitHub to demonstrate genuine development by all three
members.

### Division of Work

-   **Kemi** primarily develops the Composite hierarchy and concrete
    event structure.
-   **Boitumelo Ashley Monareng** primarily develops the Observer
    system, notices and cascading notifications.
-   **Hluyo Terrence Vakai** primarily integrates the system, develops
    the runtime demonstration, maintains the diagrams and documentation,
    and coordinates final testing.

### Recommended Branches

``` text
main
feature/composite
feature/observer
feature/integration
```

Each team member should make meaningful commits representing actual
work. Changes should be integrated into `main` after testing and review.

Actual GitHub commit and pull-request evidence should be inserted before
final submission.

------------------------------------------------------------------------

# 10. Integration and Demonstration Route

A five-minute demonstration can follow this sequence:

1.  Build the project using `make`.
2.  Run `./eventflow`.
3.  Show the nested Composite event structure.
4.  Demonstrate observer registration.
5.  Demonstrate duplicate registration handling.
6.  Trigger schedule and weather notices.
7.  Trigger a capacity threshold decision.
8.  Trigger a transport delay.
9.  Transfer the food vendor between event groups.
10. Demonstrate detach and attach behaviour.
11. Trigger evacuation and recovery.
12. Show final status/capacity traversal.
13. Demonstrate clean shutdown.

------------------------------------------------------------------------

# 11. Team Contribution Statement

  -----------------------------------------------------------------------
  Team Member                         Main Contribution
  ----------------------------------- -----------------------------------
  **Kemi**                            Composite architecture, event
                                      hierarchy, concrete leaves,
                                      ownership rules and object
                                      structure.

  **Boitumelo Ashley Monareng**       Observer architecture, notices,
                                      registration policies, cascading
                                      notifications and concrete
                                      notification behaviour.

  **Hluyo Terrence Vakai**            System integration, `main.cpp`,
                                      runtime scenarios, sequence
                                      diagrams, Doxygen, README and final
                                      testing.
  -----------------------------------------------------------------------

All three members review and understand the complete implementation, UML
diagrams, ownership policy and Observer collaboration before
demonstration.

------------------------------------------------------------------------

# 12. Submission Checklist

-   [ ] Team member names are correct.
-   [ ] Student numbers are added where required.
-   [ ] Actual GitHub repository link is added.
-   [ ] Actual commit and pull-request evidence is included.
-   [ ] Doxygen documentation is generated successfully.
-   [ ] All four sequence diagrams are rendered/exported.
-   [ ] Class and object diagrams are rendered/exported.
-   [ ] The project builds with `make`.
-   [ ] The executable is named `eventflow`.
-   [ ] The executable demonstrates Composite, Observer, registration
    changes, cascading notifications and runtime reorganisation.
-   [ ] All three members understand the complete submission.
