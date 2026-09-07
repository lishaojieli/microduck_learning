# Microduck Replication Project - Agent Instructions

## 1. Primary Goal

This repository is a long-term learning and engineering project whose final
goal is to reproduce the Pollen Robotics / Hugging Face Microduck control
stack using primarily C++.

The project is also used to learn:

- modern C++
- robot control architecture
- multithreading
- real-time control concepts
- ROS 2
- MuJoCo
- reinforcement learning / PPO
- observation and action design
- ONNX Runtime
- Raspberry Pi deployment
- real robot hardware control

The highest-priority goal is always:

> Reproduce and understand Microduck.

Do not turn this repository into a generic robotics framework.

---

## 2. Actual Repository Structure

The current repository root is:

microduck_learning/

Current structure:

microduck_learning/
├── .vscode/
├── 01_cpp_basics/
├── microduck/
│   ├── include/
│   ├── src/
│   └── CMakeLists.txt
├── .gitignore
├── README.md
└── AGENTS.md

Do not rename `microduck/` to `day03_microduck/`.

Do not reorganize the repository unless explicitly requested.

---

## 3. Directory Responsibilities

### 01_cpp_basics/

This directory contains previous learning exercises.

It may contain educational implementations of:

- Servo
- Robot
- RobotState
- RobotCommand
- Controller
- 50 Hz ControlLoop
- MotionManager
- CommandMailbox
- std::thread
- mutex
- atomic
- command queues
- Stop
- EmergencyStop
- Reset
- SafetyMonitor
- fault latching
- reset safety checks

These implementations are learning milestones.

Do not delete or heavily rewrite them unless explicitly requested.

They may be consulted for concepts, but the real Microduck implementation
should progressively become independent from them.

---

### microduck/

This is the main directory for the actual Microduck replication work.

All new Microduck-specific development should normally happen here.

The project is now transitioning from generic educational robot code to
Microduck-specific code.

---

## 4. Main Project Roadmap

The intended development path is:

1. C++ foundations
2. educational virtual robot
3. 50 Hz control loop
4. state machines, command handling and safety basics
5. Microduck source-code analysis
6. Microduck data model
7. virtual Microduck
8. Microduck observation pipeline
9. Microduck action pipeline
10. MuJoCo simulation
11. PPO reinforcement learning
12. policy export to ONNX
13. C++ ONNX Runtime inference
14. ROS 2 integration
15. Raspberry Pi deployment
16. physical Microduck hardware

Do not skip several stages ahead unless explicitly requested.

---

## 5. Current Stage

The current active stage is:

Microduck data model
-> Virtual Microduck
-> ObservationBuilder

The current target architecture is:

MicroduckRobot
    |
    v
MicroduckState
    |
    v
ObservationBuilder
    |
    v
PolicyObservation
    |
    v
future ONNX Policy
    |
    v
PolicyAction
    |
    v
future ActionMapper
    |
    v
motor targets

At the current stage, normally implement only through `ObservationBuilder`.

Do not introduce ROS 2, PPO, MuJoCo, ONNX Runtime or real servo communication
yet unless explicitly requested or required for a small interface definition.

---

## 6. Expected microduck/ Structure

The Microduck directory should progressively contain:

microduck/
├── include/
│   ├── microduck_model.hpp
│   ├── microduck_types.hpp
│   ├── microduck_robot.hpp
│   └── observation_builder.hpp
│
├── src/
│   ├── microduck_robot.cpp
│   ├── observation_builder.cpp
│   └── main.cpp
│
└── CMakeLists.txt

Before creating or overwriting any of these files:

1. inspect the current repository;
2. inspect existing file contents;
3. preserve useful existing work;
4. modify incrementally.

Do not blindly overwrite files.

---

## 7. Microduck Accuracy Rules

Microduck-specific information must be treated differently from generic
educational values.

For facts such as:

- physical joint count
- policy-controlled joint count
- joint names
- joint ordering
- servo / Dynamixel IDs
- home pose
- joint limits
- control frequency
- observation layout
- observation dimension
- action dimension
- action ordering
- action scaling
- policy input normalization
- IMU representation
- projected gravity calculation
- mouth participation in policy
- actuator mapping

prefer official sources from:

- Pollen Robotics Microduck repository
- Pollen Robotics microduck_rl repository
- official associated documentation

Verify values before encoding them as facts.

Do not assume that a number from an earlier learning exercise or chat is
necessarily an official Microduck value.

If a Microduck-specific value cannot currently be verified:

- do not invent it;
- mark it clearly as TODO or placeholder;
- centralize it in `microduck_model.hpp` where possible;
- explain the uncertainty.

Never scatter unverified robot constants throughout the source code.

---

## 8. C++ Design Rules

Use C++17 unless the project explicitly moves to a newer standard.

Prefer:

- `std::array` for fixed-size robot data
- `constexpr` for compile-time constants
- `enum class`
- `const` references
- RAII
- explicit types
- range-based loops when readable
- `std::size_t` for indices
- clear namespaces or prefixes where useful

Avoid:

- raw `new` and `delete`
- global mutable state
- unnecessary inheritance
- unnecessary templates
- excessive abstraction
- excessive design patterns
- magic numbers
- avoidable heap allocation in control-critical paths

The code must remain understandable to a student actively learning C++.

Do not optimize for cleverness.

Optimize for:

1. correctness;
2. Microduck fidelity;
3. readability;
4. deterministic behavior.

---

## 9. Fixed-Size Robot Data

Microduck robot dimensions are fixed.

For fixed-size state, observation and action data, prefer:

`std::array`

rather than:

`std::vector`

unless there is a concrete reason that the size must change at runtime.

Examples include:

- joint positions
- joint velocities
- policy actions
- observations
- IMU vectors
- fixed mappings

Avoid dynamic allocation during observation or control calculations.

---

## 10. File Responsibilities

### microduck_model.hpp

Contains fixed Microduck model definitions and constants.

Examples:

- `MicroduckJoint`
- joint count
- policy action size
- observation size
- joint names
- servo IDs
- policy-to-physical-joint mappings
- verified home pose
- verified fixed constants

Do not store changing runtime state here.

---

### microduck_types.hpp

Contains simple runtime data structures.

Examples:

- `MicroduckImuState`
- `MicroduckState`
- `PolicyCommand`
- `PolicyAction`
- `PolicyObservation`

Keep these structures primarily data-only.

Avoid large amounts of behavior inside them.

---

### microduck_robot.hpp
### microduck_robot.cpp

Implement the current virtual Microduck interface.

The external interface should gradually stabilize around operations such as:

- construction
- reading state
- setting joint targets
- updating the virtual robot

The current implementation does not need real physics.

It is an educational replacement for the future chain:

Virtual Microduck
-> MuJoCo
-> real hardware interface

Do not create fake physical realism merely to make the class more complicated.

---

### observation_builder.hpp
### observation_builder.cpp

This is a core Microduck replication component.

Its job is conceptually:

MicroduckState
+
PolicyCommand
+
previous PolicyAction
->
PolicyObservation

Requirements:

- observation size is fixed;
- use `std::array`;
- avoid heap allocation;
- avoid magic indices;
- define clear offsets;
- preserve the exact official observation ordering;
- document each section.

Prefer constants such as:

- `kGyroOffset`
- `kProjectedGravityOffset`
- `kJointPositionOffset`
- `kJointVelocityOffset`
- `kLastActionOffset`
- `kCommandOffset`

but actual sizes and ordering must be verified from the official Microduck
implementation before being treated as final.

If the real policy uses projected gravity derived from orientation, implement
that transformation rather than simply placing quaternion values into the
observation.

---

### main.cpp

`main.cpp` is currently a test entry point.

Keep it small.

It may:

- construct `MicroduckRobot`;
- read `MicroduckState`;
- create test policy commands;
- create zero previous actions;
- build observations;
- print useful verification information.

Do not place major control or robot logic directly inside `main.cpp`.

---

## 11. CMake Rules

The active Microduck CMake project is:

microduck/CMakeLists.txt

Use CMake.

Maintain Windows compatibility.

Use C++17.

Do not add third-party libraries until they are actually required.

After modifying buildable code:

1. configure CMake;
2. build it;
3. inspect compiler errors;
4. fix errors;
5. rebuild;
6. run the executable when practical.

Do not report that the project compiles unless compilation was actually
performed successfully.

---

## 12. Real-Time Direction

The system is not currently a hard real-time controller.

However, code should move toward predictable control-loop behavior.

Microduck eventually requires a periodic robot control loop.

Therefore, in control-critical code:

- avoid file I/O;
- avoid blocking input;
- avoid unnecessary heap allocation;
- prefer fixed-size containers;
- avoid unpredictable expensive operations;
- keep control calculations deterministic.

Do not prematurely introduce a complex real-time framework.

---

## 13. Learning Requirements

This project is not only about producing working code.

Important changes should also teach the user why they exist.

After a substantial implementation task, explain:

1. what was changed;
2. what each relevant file does;
3. how the data flows;
4. which part corresponds to official Microduck;
5. which values are officially verified;
6. which values remain placeholders;
7. important C++ concepts introduced;
8. how to build and test the code;
9. what the next Microduck-specific step should be.

Do not introduce large amounts of unrelated theory.

---

## 14. Do Not Drift

Before adding a significant module, ask:

> Does this directly help reproduce or understand Microduck?

If the answer is no, do not implement it unless it is a necessary prerequisite.

Do not spend multiple stages building generic:

- command frameworks
- safety frameworks
- hardware abstraction frameworks
- plugin architectures
- messaging frameworks
- robotics middleware
- generic robot base classes

unless Microduck actually requires them at the current stage.

The project path must remain:

Microduck model
-> observation/action
-> MuJoCo
-> PPO
-> ONNX
-> ROS 2
-> Raspberry Pi
-> physical robot

---

## 15. Source Inspection Before Modification

When beginning a task:

1. read this `AGENTS.md`;
2. inspect the repository structure;
3. read relevant current source files;
4. inspect `microduck/CMakeLists.txt`;
5. understand existing implementation;
6. then modify files.

Do not assume the repository still looks exactly like a previous conversation.

The repository itself is the source of truth for current code state.

---

## 16. Git Safety

Do not delete unrelated user work.

Do not rewrite git history.

Do not perform destructive Git operations unless explicitly requested.

Before large changes, inspect:

`git status`

After completing changes, clearly report which files were modified.

Do not create commits unless explicitly requested by the user.

---

## 17. Current Immediate Objective

The immediate implementation objective is to establish and validate:

- `microduck_model.hpp`
- `microduck_types.hpp`
- `microduck_robot.hpp`
- `microduck_robot.cpp`
- `observation_builder.hpp`
- `observation_builder.cpp`
- `main.cpp`
- `CMakeLists.txt`

The main milestone is:

MicroduckState
->
ObservationBuilder
->
correct fixed-size Microduck PolicyObservation

Do not move to the next major subsystem until this data contract has been
verified.