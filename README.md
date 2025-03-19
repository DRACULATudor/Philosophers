## Introduction

The **Philosophers** project is a classic problem in multithreading and synchronization, designed to teach how to manage multiple threads and shared resources in a concurrent environment. The problem involves simulating a number of philosophers sitting at a round table, each thinking and eating. The challenge is to ensure that the philosophers do not starve and do not cause deadlocks while sharing limited resources (forks) in the process.

The goal of this project is to simulate the philosophers' behavior and implement solutions to ensure that:
- Philosophers can think and eat without deadlocking.
- Philosophers do not starve (i.e., they get a chance to eat).
- The program properly handles synchronization issues using threads and mutexes.

You will learn to manage threads, use synchronization tools, avoid race conditions, and apply best practices to implement a solution that works under the constraints of the problem.

This project requires a deep understanding of thread management, synchronization techniques (like mutexes and condition variables), and the careful handling of shared resources to avoid issues like deadlock and starvation.

## Compilation

```
make
```
Or, if there is no Makefile:
```
c++ -Wall -Wextra -Werror -std=c++98 *.cpp -o program
```
Run the program:
```
./exec_name(check Makefile) [number_of_philos] [timestamp_to_die_in_ms] [timestamp_to_eat_in_ms] [timestamp_to_sleep_in_ms] (optional arg [number_of_meals])

```


## Topics Covered

### 1. **Threads and Synchronization**
   - **Creating Threads**: Using the `pthread` library to create multiple threads in a program.
   - **Mutexes and Locks**: Managing shared resources using `pthread_mutex_t` to ensure threads don’t interfere with each other.
   - **Condition Variables**: Using condition variables to control when threads can proceed, ensuring correct timing and synchronization.

### 2. **Deadlock Prevention and Handling**
   - **Deadlock**: Understanding and avoiding situations where two or more threads are stuck waiting for each other to release resources.
   - **Strategies for Prevention**: Implementing strategies to avoid deadlocks, such as always acquiring locks in a consistent order.

### 3. **Philosophers' Problem**
   - Simulating the behavior of philosophers sitting at a table, thinking, and eating from shared resources (forks).
   - **Resource Management**: Ensuring that each philosopher can eat without deadlocking or starving, using proper synchronization.

### 4. **Timers and Sleep Functions**
   - Using `usleep()` or similar functions to simulate the time philosophers spend eating or thinking.
   - **Time Control**: Managing the timing of each philosopher’s actions to mimic real-world behavior (e.g., thinking for a certain amount of time before eating).

### 5. **Memory Management**
   - Proper allocation and deallocation of memory for threads, mutexes, and shared resources.
   - **Avoiding Memory Leaks**: Ensuring that all resources are properly freed when no longer needed, particularly with dynamically allocated memory.

### 6. **Multithreading Best Practices**
   - Writing thread-safe code using mutexes and other synchronization tools to ensure the program runs smoothly and efficiently.
   - Handling concurrency issues such as race conditions and ensuring that threads operate without interfering with each other.
