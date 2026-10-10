*This activity has been created as part of the 42 curriculum by mkhashan.*

# Codexion

## Description
Codexion is a multi-threaded simulation of coders working on a project. The goal is to simulate the process of coding, compiling, debugging, and refactoring while managing shared resources (dongles) and handling coder burnout. The project demonstrates complex thread synchronization, scheduling policies (FIFO and EDF), and the management of shared state in a concurrent environment.

## Instructions

### Compilation
The project includes a `makefile`. To compile the project, run:
```bash
make
```

### Execution
The program takes several arguments to configure the simulation. The general format is:
```bash
./Codexion <num_coders> <burnout_time> <compile_time> <debug_time> <refactor_time> <compiles_required> <dongle_cooldown> <policy>
```

**Arguments:**
- `num_coders`: Number of coders in the simulation.
- `burnout_time`: Time before a coder burns out.
- `compile_time`: Time taken to compile.
- `debug_time`: Time taken to debug.
- `refactor_time`: Time taken to refactor.
- `compiles_required`: Number of successful compilations required to finish.
- `dongle_cooldown`: Cooldown period for dongles.
- `policy`: Scheduling policy (`fifo` or `edf`).

**Example:**
```bash
./Codexion 5 500 100 100 100 3 10 edf
```

### Cleaning
To remove object files:
```bash
make clean
```
To remove the executable:
```bash
make fclean
```
To recompile:
```bash
make re
```

## Blocking cases handled
The implementation addresses several critical concurrency and synchronization issues:

- **Deadlock Prevention:** To prevent deadlocks when acquiring multiple dongles, the system follows a strict locking order based on coder index.
- **Coffman's Conditions:** By ensuring that resources (dongles) are acquired in a consistent order and avoiding circular wait, the implementation breaks the necessary conditions for deadlock.
- **Starvation Prevention:** The use of scheduling policies (FIFO and EDF) ensures that coders are served based on defined priorities or arrival times, preventing any single thread from being indefinitely ignored.
- **Cooldown Handling:** The simulation tracks the `last_used` timestamp of each dongle. Coders are only allowed to acquire dongles if the specified `dongle_cooldown` period has passed since the dongle's last use.
- **Precise Burnout Detection:** The system monitors the time elapsed since a coder last made progress. If the time exceeds `time_to_burnout`, the coder is marked as burned out.
- **Log Serialization:** Thread-safe logging is implemented to ensure that output from different threads does not overlap or become corrupted, maintaining a clear chronological record of simulation events.

## Thread synchronization mechanisms
The project utilizes several POSIX threading primitives to coordinate access to shared resources:

- **`pthread_mutex_t`**: 
  - **Dongle Mutexes**: Each dongle has its own mutex to ensure that only one thread can modify its state or check its availability at a time.
  - **Coder State Mutexes**: Used to protect the internal state of each coder (e.g., `is_alive`, `compilation_times`).
  - **Global State Mutexes**: Used for coordinating access to the shared simulation state and the scheduler queue.
- **`pthread_cond_t`**: 
  - **Wait/Signal Pattern**: Coders wait on condition variables when they are unable to acquire necessary dongles or when they are waiting for their turn in the scheduler. The monitor thread signals these variables when resources become available or the scheduler decides it is the coder's turn.
- **Custom Event Implementation**:
  - The monitor acts as a central coordinator, checking the state of the queue and the availability of dongles, then signaling the appropriate coder threads to wake up and proceed.

**Example of Race Condition Prevention:**
When a coder attempts to acquire two dongles (their own and the neighbor's), they lock the mutexes in a fixed order (index $i$ then index $i+1$). This prevents a race condition where two adjacent coders try to lock the same two dongles in opposite orders, which would lead to a deadlock.

## Resources
### References
- [POSIX Threads (man pages)](https://man7.org/linux/man-pages/man7/pthreads.7.html)
- [The C Programming Language (K&R)](https://en.wikipedia.org/wiki/The_C_Programming_Language)
- [Operating Systems: Three Easy Pieces (OSTEP)](https://ostep.org/)

### AI Usage
AI was used in the following ways:
- **Architecture Design**: Assisting in the structural layout of the project and the relationship between the monitor and coder threads.
- **Debugging**: Analyzing complex race conditions and providing suggestions for deadlock prevention.
- **Documentation**: Generating the initial draft of this README.md based on the code implementation.
