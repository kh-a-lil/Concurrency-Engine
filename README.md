*This project has been created as part of the 42 curriculum by kraghib.*

# Codexion

## Description
Codexion is a complex concurrency and multithreading simulation built in C. Inspired by the classic Dining Philosophers problem, this project models a high-stakes, time-sensitive collaborative coding environment. Multiple "coders" sit at a circular table and must share limited resources (USB dongles) to compile their code.

The project goes beyond standard mutex locking by introducing **Priority Scheduling** (FIFO and Earliest Deadline First), **Resource Cooldowns**, and extremely strict timing requirements. The goal is to orchestrate these concurrent threads without any data races, deadlocks, or resource starvation, while ensuring no coder "burns out" due to lack of resources.

## Instructions

**Compilation:**
The project includes a standard Makefile. Run the following command at the root of the repository to compile the executable:
```bash
make
```

**Execution:**
The program takes the following arguments:
```bash
./codexion [number_of_coders] [time_to_burnout] [time_to_compile] [time_to_debug] [time_to_refactor] [number_of_compiles_required] [dongle_cooldown] [scheduler]
```
*Note: All time parameters are in milliseconds. The scheduler must be exactly `fifo` or `edf`.*

**Example:**
Run a simulation with 5 coders, an 800ms burnout limit, 200ms task times, 5 compiles required per coder, a 10ms dongle cooldown, using First-In-First-Out scheduling:
```bash
./codexion 5 800 200 200 200 5 10 fifo
```

## Resources
*   **Operating Systems: Three Easy Pieces (OSTEP)** - Chapters on Concurrency, Mutexes, and Condition Variables.
*   **LLNL POSIX Threads Programming Tutorial** - Comprehensive documentation on the `pthread` API.
*   **AI Usage:** Artificial Intelligence (Claude 3.5 Sonnet) was used during this project as an interactive structural guide and rubber-duck debugger. Specifically, AI was utilized to:
    *   Analyze multithreading edge cases regarding "Lost Wakeups" to safely design the `pthread_cond_timedwait` logic.
    *   Optimize the binary Min-Heap array algorithm, dynamically limiting its memory footprint to exactly 2 nodes based on the mathematical maximum load of the circular table geometry.

---

## Blocking cases handled

*   **Deadlock Prevention (Coffman's Conditions):** A classic circular wait deadlock is prevented by implementing a strict **Resource Hierarchy**. During initialization, even-numbered coders are assigned their left dongle first, then their right. Odd-numbered coders request their right dongle first, then their left. This mathematically breaks the circular wait condition.
*   **Starvation Prevention:** Addressed through the mandatory implementation of a Priority Queue (Min-Heap). Depending on the chosen argument, dongles are granted either strictly by arrival time (FIFO) or by the proximity of the coder's death timestamp (EDF).
*   **Cooldown Handling:** Handled asynchronously. Instead of blocking the CPU with a `usleep` during a dongle's cooldown, the thread checks the `available_at` timestamp and utilizes `pthread_cond_timedwait`. This allows the thread to sleep efficiently at the OS level while respecting the exact millisecond the cooldown expires.
*   **Precise Burnout Detection:** A dedicated, single `monitor` thread continuously polls the `last_compile_start` of all coders. Because the monitor runs independently of the coders' sleeping/working routines, it can instantly detect and report a burnout within the strict 10ms tolerance.
*   **Log Serialization:** A dedicated `print_lock` mutex ensures that `printf` output is strictly serialized. No two state messages (e.g., "is compiling", "has taken a dongle") can ever interleave or become corrupted on `stdout`.

## Thread synchronization mechanisms

My implementation relies entirely on the POSIX threads API, specifically utilizing `pthread_mutex_t` and `pthread_cond_t` primitives to ensure a thread-safe environment.

*   **Protecting Shared State (`pthread_mutex_t`):**
    Every piece of shared memory is shielded by a specific mutex. For example, the `state_lock` mutex protects the global `sim_stop` flag. When the monitor detects a death, it locks the state, flips the flag, and unlocks it. The coder threads briefly lock `state_lock` to read this flag, preventing torn reads or data races. Each coder also has a personal `lock` to protect their `last_compile_start` variable from being read by the monitor while it is actively being updated.
*   **Dongle Arbitration (`pthread_cond_t`):**
    Instead of CPU-intensive busy-waiting (spinning in a `while` loop), coders use Condition Variables (`cond`). When a coder requests a dongle that is currently used, they are placed into `pthread_cond_wait`. This function atomically unlocks the dongle's mutex and puts the thread to sleep.
*   **Thread-Safe Communication:**
    When a coder finishes using a dongle, they update its state (`is_used = 0`), calculate the cooldown, and call `pthread_cond_broadcast`. This acts as a signal to the OS to wake up all sleeping threads waiting for that dongle. The woken threads re-acquire the mutex and check the priority queue to see whose turn it is.
    Furthermore, if the monitor detects a death, it updates the `sim_stop` flag and immediately broadcasts to all condition variables, ensuring any threads sleeping in queues instantly wake up, realize the simulation has ended, and cleanly exit.


