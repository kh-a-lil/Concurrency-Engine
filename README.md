*This project has been created as part of the 42 curriculum by [your_login].*

## Description
Codexion is a concurrency simulation inspired by the classic Dining Philosophers problem. It simulates a collaborative coding environment where developers must share a limited number of USB dongles to compile quantum code. The project emphasizes thread synchronization, deadlock prevention, and scheduling (FIFO and Earliest Deadline First) using POSIX threads and mutexes.

## Instructions
**Compilation:** Run `make` inside the `coders/` directory to compile the `codexion` executable.
**Execution:** `./codexion [nb_coders] [t_burnout] [t_compile] [t_debug] [t_refactor] [nb_compiles][cooldown] [scheduler]`
**Example:** `./codexion 3 1500 400 200 200 5 100 fifo`

## Resources
- "Operating Systems: Three Easy Pieces" - Concurrency and Threads.
- POSIX Threads Programming (LLNL Tutorial).
- AI was used as a structural guide to organize the program architecture, write the Makefile template, and generate ideas for a simplified array-based priority queue.

## Blocking cases handled
- **Deadlock Prevention (Coffman's conditions):** Handled by introducing a resource hierarchy. Coders always request the lower-numbered dongle ID first before requesting the higher-numbered one, breaking the circular wait condition.
- **Starvation Prevention:** Addressed via the strict implementation of FIFO and EDF priority queues for dongle arbitration.
- **Cooldown Handling:** Managed by storing an `available_at` timestamp on each dongle and enforcing it via condition variables.
- **Precise Burnout Detection:** Achieved by dedicating a separate monitor thread that continuously polls coder timestamps without being blocked by sleep/mutex states.
- **Log Serialization:** A dedicated `print_lock` mutex ensures no two output lines interleave.

## Thread synchronization mechanisms
- **pthread_mutex_t:** Used to protect the state of each shared resource (dongles), to serialize standard output (`print_lock`), and to protect simulation state variables (`state_lock`).
- **pthread_cond_t:** Condition variables are attached to each dongle. Instead of busy-waiting, coders use `pthread_cond_wait` to sleep until a dongle is released, at which point the releaser calls `pthread_cond_broadcast`.
- **Race conditions:** Prevented by ensuring that any read or write to shared variables (like `is_used` or `last_compile_start`) is wrapped in its respective mutex lock.
