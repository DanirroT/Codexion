*This project has been created as part of the 42 curriculum by dmota-ri*

# Description

Codexion is designed to teach students how to manage Threads Mutexes and Conditions in C with specific purposes to each.


The goal is to create an **Simulation** of multiple **Coders** working together to **Compile**, **Debug** and **Refract** Code into a central console by the means of a limited supply of **Dongles** that needs to be managed for the best possible efficiency snd to try and evade **Burnout** at every turn.

# Instructions”

For compilation, a Makefile is provided. Running the command `make` on a shell console will compile the program.


The output of this compilation will be a codexion executable.
To use it as intended, run it with a set of arguments in the following order:

- `number_of_coders` - Number of **Coders** and **Dongles** present for the Simulation.
- `time_to_burnout` - if a **Coder** does not start **compiling** after this amount of time, starting from the moment they started **compiling** for the last time, the **Coder** will burnout.
- `time_to_compile` - Time needed to **Compile** code. Requite **Dongles**.
- `time_to_debug` - Time needed to **Debug** code. Does not requite **Dongles**.
- `time_to_refactor` - Time needed to **Refractor** code. Does not requite **Dongles**.
- `number_of_compiles_required` - the number of **Compilations** each coder has to complete for the **Simulation** to end in a Success.
- `dongle_cooldown` - Time a dongle needs to cooldown after use.
- `scheduler` - The decision mechanism used by **Dongles** to decide who gets one
when multiple coders request them.
The value must be exactly one of: `fifo` or `edf`.
  - `fifo` means First In, First Out: the `Dongle` is given to the **Coder** whose request arrived first.
  - `edf` means Earliest Deadline First with `deadline = last_compile_start + time_to_burnout`.

- example:
  - `./codexion 4 400 200 200 200 3 100 fifo`

when running, a live log will be displayed wit hall the actions taken by each **Coder**. the listed actions are formatted as follows:

- `timestamp Coder Action`
  - timestamp is the time in milliseconds since the start of the Simulation
  - Coder will be the ID of the Coder in question, ranging from 1 to `number_of_coders`
  - Action will be the Action taken. 5 Actions are possible>
    - `has taken a dongle` - **Coder** takes one of the **Dongles**
    - `is compiling` - **Coder** starts **Compiling**
    - `is debugging` - **Coder** starts **Debugging**
    - `is refactoring` - **Coder** starts **Refactoring**
    - `burned out` - **Coder** starts Burned Out, meaning, it has failed to start **Compiling** in `time_to_burnout`

# Resources”

Most of the core concepts i Learned from Evaluating others and pure experimentation, i needed only to look up how the Thread functions were called properly ad not much other research was necessary past the understanding of how threads fundamentally worked


For further explanation of particular aspects of internal Thread Logic or strange errors i was not able ti find elsewhere, I sometimes checked in with AI with mixed results. I also used it as a tool to sift through the lengthy error messages I am not yet familiar with (my own in-built debugging outputs while in development and Valgrind memory testing output, for example).

listing classic references related to the topic (documentation, articles, tutorials, etc.), as well as a description of how AI was used — specifying for which tasks and which parts of the project.


# Blocking cases handled”
describing all the concurrency issues addressed in your solution (e.g., deadlock prevention and Coffman’s conditions, starvation prevention, cooldown handling, precise burnout detection, and log serialization).

# Thread synchronization mechanisms”
explaining the specific threading primitives used in your implementation (pthread_mutex_t, pthread_cond_t,
custom event implementation) and how they coordinate access to shared resources
(dongles, logging, monitor state). Include examples of how race conditions are
prevented and how thread-safe communication is achieved between coders and the
monitor.

## Sources:
Thread Functions list and explanation:
- https://www.geeksforgeeks.org/c/thread-functions-in-c-c/
Time Functions Help:
- https://man7.org/linux/man-pages/man3/usleep.3.html
- https://man7.org/linux/man-pages/man2/settimeofday.2.html
- https://man7.org/linux/man-pages/man3/timeval.3type.html
- https://man7.org/linux/man-pages/man3/timespec.3type.html
