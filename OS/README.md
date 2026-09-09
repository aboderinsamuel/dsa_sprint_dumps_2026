# C++ Interview Course

Start with [00_course_map.md](00_course_map.md). It explains the order, vocabulary, and interview framework. The `.cpp` files are deliberately small and runnable; comments move from beginner explanations to technical details.

For detailed definitions, read [00_glossary.md](00_glossary.md). It explains
each important term in plain English, technically, and with small examples.

## Recommended order

1. [01_pointers.cpp](01_pointers.cpp): pointers, references, and smart-pointer ownership.
2. [02_stack_heap_raii.cpp](02_stack_heap_raii.cpp): stack, heap, destructors, and RAII.
3. [03_copy_move.cpp](03_copy_move.cpp): copying, moving, and Rule of 0/3/5.
4. [04_thread_basics.cpp](04_thread_basics.cpp): starting, joining, and safely owning threads.
5. [05_race_and_mutex.cpp](05_race_and_mutex.cpp): data races and mutex protection.
6. [06_deadlocks.cpp](06_deadlocks.cpp): deadlocks, lock ordering, and `scoped_lock`.
7. [03_condition_variable.cpp](03_condition_variable.cpp): waiting and producer/consumer queues.
8. [08_atomic_and_memory_order.cpp](08_atomic_and_memory_order.cpp): atomics and acquire/release.
9. [09_shared_mutex.cpp](09_shared_mutex.cpp): multiple readers and exclusive writers.
10. [10_futures.cpp](10_futures.cpp): results and exceptions from asynchronous work.
11. [11_thread_pool.cpp](11_thread_pool.cpp): reusable workers and clean shutdown.
12. [12_thread_safe_order_book.cpp](12_thread_safe_order_book.cpp): trading-style shared state and invariants.

## Compile and run

From the workspace root, with MinGW g++:

```text
g++ -std=c++17 -pthread OS/01_pointers.cpp -o OS/01_pointers.exe
OS/01_pointers.exe
```

Replace `01_pointers.cpp` with any lesson. Build with C++17 or newer. Thread scheduling is nondeterministic, so output order from different threads can vary.

## What “thread-safe” means

- Identify shared memory.
- Identify the invariant, such as “available quantity never becomes negative.”
- Keep the check and update that preserve the invariant under the same lock.
- Use RAII lock types so exceptions and early returns release locks.
- Join worker threads before referenced objects are destroyed.
- Do not expose references or iterators into a container while another thread can mutate it.

## Honest scope

This is comprehensive for the practical C++ ownership and concurrency core used in many systems, backend, and trading interviews. No small repository can cover all of C++ or every operating-system topic. After these chapters, study algorithms, operating systems, networking, databases, CPU caches, profiling, and target-company-specific systems design. Advanced follow-ups include coroutines, executors, lock-free memory reclamation, custom allocators, semaphores, latches, barriers, and cache-line alignment.
