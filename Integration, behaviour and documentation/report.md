# COS 214 Practical 3 — EventFlow Design Report

> **Submission template:** replace the team placeholders and GitHub placeholder before submission.

## 1. Event name and concept

### Pretoria Innovation Expo 2026

Pretoria Innovation Expo is a live technology exhibition containing presentation areas, interactive demonstrations, visitor services, transport and security operations. The event is intentionally modelled as a hierarchy because an organiser can reason about a whole expo, a hall, a zone, or one operational unit using the same `EventComponent` interface.

The sample tree is:

```text
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

The design contains six concrete leaf types: `DemoStage`, `InnovationBooth`, `InformationDesk`, `ShuttleStop`, `SecurityTeam`, and `FoodVendor`.

The grouping types are represented by `EventGroup` instances such as the root expo, halls and zones. There are at least three nesting levels below the client/root boundary: root → hall → zone → leaf.

## 1.2 GoF participant mapping

### Composite

| GoF role | EventFlow class | Responsibility |
|---|---|---|
| Component | `EventComponent` | Uniform `open`, `close`, `reportStatus`, `getCapacity`, `getName` operations. |
| Composite | `EventGroup` | Owns zero or more `EventComponent` children and recursively implements common operations. |
| Leaf | `EventUnit` and six concrete leaf classes | Performs concrete operational behaviour. |
| Client | `main.cpp` / event operator | Builds and uses the tree through `EventComponent`. |

### Observer

| GoF role | EventFlow class | Responsibility |
|---|---|---|
| Subject | `Subject` | Registration list and notification protocol. |
| Concrete Subject | `EventControl` and `EventGroup` | Publishes notices. `EventControl` originates event-wide notices; groups cascade them. |
| Observer | `Observer` | Notification interface and safe registration bookkeeping. |
| Concrete Observers | `EventGroup` and six concrete event units | React polymorphically to notices. |

`EventGroup` participates in three collaborations: Composite as a structural node, Observer as a receiver from its parent, and Subject as a publisher to interested descendants. These are different reasons for collaboration and are not the same pattern.

## 1.3 Architecture summary

`EventComponent` is the polymorphic Composite boundary. `EventGroup` contains owning `EventComponent*` children. `EventControl` owns neither the Composite tree nor observers. Instead, observer pointers are non-owning registrations.

The observer chain is configured separately from the ownership tree. A representative chain is:

```text
EventControl
    ↓ observes
root EventGroup
    ↓ observes
Tech Hall
    ↓ observes
Future Mobility Zone
    ↓ observes
DemoStage / Robotics Demo Booth
```

This separation makes it possible to reorganise ownership without automatically changing every notification relationship.

## 1.4 Design rationale

### Genuine part-whole tree

A hall is genuinely made up of zones and operational units. A zone can contain other groups and leaves, and the same common operations make sense at every level. `getCapacity()` recursively aggregates children and `open()`, `close()` and `reportStatus()` recursively traverse the subtree. A client therefore does not need to know whether a reference is a leaf or an entire area.

### Why Observer is needed

Direct calls from `EventControl` to every concrete unit would hard-code the event topology and force the controller to know every class. Observer lets new interested components register at runtime without modifying `EventControl`. Groups can also receive a notice and republish it to their own registered observers.

### Ownership

Each `EventGroup` owns its direct children. Successful `add()` transfers ownership to that group. `remove()` does not delete the child; it transfers ownership back to the caller. This rule makes runtime movement possible without double deletion.

### Observer ownership

Subjects do **not** own observers. The observer list contains non-owning raw pointers. This is appropriate because the Composite tree already defines component ownership, while observation is a separate relationship. `Observer` remembers its registered subjects and unregisters from them in its destructor. `Subject` also informs observers when a subject is destroyed. Together these mechanisms prevent dangling registration entries under normal destruction.

### Registration policy

- `attach(nullptr)`: ignored.
- Duplicate `attach(same pointer)`: ignored.
- `detach(nullptr)`: ignored.
- `detach(unregistered pointer)`: no-op.
- During notification, the Subject iterates over a snapshot. Registration changes therefore do not invalidate the current iteration.

## 1.5 Push/pull choice

EventFlow uses **push**. The operation is `update(const Notice&)`, and `Subject::notify()` passes the complete `Notice` to the observer. The notice contains `type`, `message` and `value`.

Push is useful here because capacity values, schedule information and safety messages are already known at publication time. It avoids a second query and makes the sequence diagrams explicit. The trade-off is that `Notice` must contain enough information for observers, so a very large event state object should not be pushed unnecessarily.

## 2. Composite implementation

`EventGroup::add()` stores an owned child pointer. `remove()` erases a direct child and returns its pointer without deleting it. Recursive operations iterate over `children_` and call the same `EventComponent` interface on every child.

The root deletion demonstration in `main.cpp` executes `delete expo`. The `EventGroup` destructor deletes each child exactly once. Because children are removed from their previous parent before a transfer, a moved unit cannot be deleted by both parents.

## 3. Observer notification system

The concrete subject is `EventControl`. It stores the current notice and calls `notify()`. `EventGroup` is both an Observer and a Subject: its `update()` stores the pushed notice and then calls its own `notify()`.

This gives a multi-level cascade such as:

```text
EventControl
 → Pretoria Innovation Expo
   → Tech Hall
     → Future Mobility Zone
       → Keynote Stage / Robotics Demo Booth
```

The concrete leaf classes have genuinely different reactions. For example, a weather alert pauses the stage, keeps the information desk in guidance mode, leaves the booth operational, and changes security's monitoring state.

## 3.3 Notice/order types

The implementation provides ten notice types:

1. `OPEN` — operational opening.
2. `CLOSE` — operational closure.
3. `SCHEDULE_CHANGE` — timetable update.
4. `CAPACITY_ALERT` — aggregate crowd/capacity warning.
5. `WEATHER_ALERT` — weather risk.
6. `TRANSPORT_DELAY` — shuttle delay.
7. `EVACUATE` — safety evacuation.
8. `PAUSE` — temporary pause.
9. `RESUME` — recovery after a pause/emergency.
10. `STOCK_ALERT` — food-service stock warning.

These cover ordinary operational, capacity-related and safety-related changes.

## 4. Event rules

1. **Weather:** `DemoStage` pauses its outdoor performance, while `InformationDesk` remains active to broadcast guidance.
2. **Capacity:** `InnovationBooth` limits queue intake and `SecurityTeam` increases crowd-control readiness.
3. **Transport:** `ShuttleStop` changes its operational state and passenger messaging when a transport delay arrives.
4. **Evacuation:** `SecurityTeam` deploys an evacuation perimeter, `FoodVendor` secures equipment, `DemoStage` clears performers/audience, and `InformationDesk` enters evacuation-guidance mode.
5. **Schedule:** `DemoStage`, `InnovationBooth` and `InformationDesk` each update different operational information when a schedule changes.
6. **Recovery:** `RESUME` returns a paused stage to normal operation while the system continues to respect the current observer registrations.

These behaviours are selected by each concrete Observer's polymorphic `update()` implementation. `EventControl` never asks an object what concrete type it is.

## 4.2 Runtime reorganisation

`Future Bites Vendor` starts under `Community Hall`. During execution it is removed from `Community Hall` and added to `Tech Hall`. Before transfer, the vendor is detached from `Community Hall` as an Observer. After transfer it is attached to `Tech Hall`.

The ownership and observation changes are deliberately separate:

```text
communityHall.remove("Future Bites Vendor")
communityHall.detach(cafe)
techHall.add(cafe)
techHall.attach(cafe)
```

No deletion occurs during the transfer.

## 4.3 Condition-based decision

`EventControl::evaluateCapacity(EventGroup*, int)` calls the Composite's `getCapacity()` and `capacityAtLeast()`. If the threshold is reached, it issues a `CAPACITY_ALERT`; otherwise no warning is issued. This condition is represented by the `alt` fragment in SD3. The `opt` fragment represents an additional high-pressure response.

## 4.4 Original features

### Stock-aware catering

`STOCK_ALERT` causes `FoodVendor` to switch to a stock-conserving menu. This is separated into the leaf's behaviour rather than adding food logic to `EventControl`.

### Visitor guidance mode

`InformationDesk` remains operational during weather and evacuation notices, changing the service it provides instead of simply closing like an ordinary unit.

### Transport disruption handling

`ShuttleStop` reacts specifically to `TRANSPORT_DELAY` and to evacuation support. This creates a distinct operational role rather than another generic leaf.

## 5. Sequence diagram portfolio

### SD1 — Building and registering

Shows client-side creation, Composite ownership through `add()`, and separate Observer registrations. An `opt` fragment demonstrates the duplicate-registration policy.

### SD2 — Cascading event notification

Shows `EventControl` publishing a schedule change, then nested `update()`/`notify()` calls through multiple Composite levels. A `loop` fragment represents the observer list, and the push notice is visible on every `update()` call.

### SD3 — Conditional capacity response

Shows the Composite capacity query and an `alt` decision for the threshold. An `opt` fragment models an additional high-pressure response. The interaction continues through the Composite hierarchy rather than type-checking concrete units in the controller.

### SD4 — Signature safety/recovery scenario

Shows a safety notice, a registration change, runtime vendor transfer, and a recovery notice. It includes more than six lifelines, two Composite levels, observer notifications, ownership transfer, detach/attach, `loop` and `opt` fragments.

## 6. Doxygen

The project contains a `Doxyfile` configured to scan the C++ headers and source files and generate HTML under `docs/doxygen`. Public classes and public operations have Doxygen documentation, including ownership expectations for raw pointers.

Three non-obvious decisions documented in code are:

1. Observer references are non-owning.
2. Composite `remove()` transfers ownership instead of deleting.
3. Subject notification uses a snapshot to make registration changes during notification safe.

## 7. Git/GitHub workflow reflection

**Replace the placeholders below with the team's actual history. Do not invent commits.**

Member 1 should primarily own the Composite implementation and build system, Member 2 should primarily own Observer behaviour and event rules, and Member 3 should primarily own diagrams, Doxygen and integration. All members should review and understand the complete design.

A suitable workflow is a private GitHub repository with feature branches and pull requests. Commits should describe real work, for example `Implement EventGroup composite ownership`, `Add safe observer registration`, `Add capacity and safety scenarios`, and `Add UML sequence portfolio`.

Record actual evidence here:

- Commit/PR 1: `<hash/link and what changed>`
- Commit/PR 2: `<hash/link and what changed>`
- Commit/PR 3: `<hash/link and what changed>`

## 8. Integration/demonstration route

A five-minute demonstration can follow this order:

1. Build using `make`.
2. Run `./eventflow`.
3. Point out the nested Composite structure.
4. Show observer registration and duplicate-registration handling.
5. Trigger schedule and weather notices.
6. Trigger the capacity threshold decision.
7. Trigger transport delay.
8. Move the food vendor and show detach/attach.
9. Detach security, issue evacuation, then reattach security and issue resume.
10. Show the final traversal and clean root deletion.

## 9. Team contribution statement

| Member | Main contribution | Integration/evidence |
|---|---|---|
| `<Member 1>` | `<actual contribution>` | `<actual commits/PRs>` |
| `<Member 2>` | `<actual contribution>` | `<actual commits/PRs>` |
| `<Member 3>` | `<actual contribution>` | `<actual commits/PRs>` |

## Submission checklist

- [ ] Replace team names and student numbers.
- [ ] Add actual private GitHub repository link.
- [ ] Add real GitHub commit/PR evidence from all three members.
- [ ] Generate Doxygen successfully and include evidence/screenshot in the final PDF.
- [ ] Render/export all four PlantUML sequence diagrams.
- [ ] Render/export the class diagram and object diagram.
- [ ] Put this report in the required PDF order.
- [ ] Build with `make` using C++11.
- [ ] Run `./eventflow` and demonstrate the required behaviours.
