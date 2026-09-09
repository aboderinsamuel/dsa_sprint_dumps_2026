# C++ Interview Course Map

This course is intentionally repetitive. Every topic appears in three forms:

1. **Plain English:** what the idea means without jargon.
2. **Technical view:** what the C++ language and runtime guarantee.
3. **Code:** a small example you can compile, run, and modify.

Start with [00_glossary.md](00_glossary.md) when a word such as mutex, atomic,
RAII, or condition variable is unfamiliar. Each definition includes plain
English, technical meaning, and a small example.

## Study rule

Do not only read the output. Before running a file, predict the output. Then change one line, run it again, and explain why the result changed.

## Chapters

| File | Topic | Interview result |
|---|---|---|
| `01_pointers.cpp` | Addresses, pointers, references, smart pointers | Explain ownership and lifetime |
| `02_stack_heap_raii.cpp` | Stack, heap, destructors, RAII | Explain automatic cleanup |
| `03_copy_move.cpp` | Copy/move constructors and assignments | Explain Rule of 0/3/5 |
| `04_thread_basics.cpp` | Start, join, detach, lifetime | Explain safe thread ownership |
| `05_race_and_mutex.cpp` | Data races and basic locking | Protect shared state |
| `06_deadlocks.cpp` | Deadlocks and lock ordering | Design safe multi-lock code |
| `03_condition_variable.cpp` | Waiting and producer/consumer | Coordinate threads efficiently |
| `08_atomic_and_memory_order.cpp` | Atomics and visibility | Choose atomic vs mutex |
| `09_shared_mutex.cpp` | Many readers, few writers | Discuss read/write contention |
| `10_futures.cpp` | Exceptions and results from threads | Return work results safely |
| `11_thread_pool.cpp` | Reusable worker threads | Explain production-style work execution |
| `12_thread_safe_order_book.cpp` | Trading-style shared map | Preserve invariants under concurrency |

## The vocabulary you must be able to say out loud

- **Thread:** one path of execution inside a process.
- **Shared state:** data accessible by more than one thread.
- **Data race:** conflicting unsynchronized memory accesses, with at least one write. In C++, this is undefined behavior.
- **Race condition:** a result that depends on timing. A race condition can exist even when the program is technically synchronized; a data race is specifically an invalid unsynchronized memory access.
- **Critical section:** code that accesses shared state and must be protected as one unit.
- **Mutex:** a mutual-exclusion lock. One thread owns it at a time.
- **RAII:** acquire a resource in an object's constructor and release it in its destructor.
- **Deadlock:** threads wait forever because each needs a resource held by another.
- **Liveness:** whether the program continues making progress. Deadlock and starvation are liveness failures.
- **Atomic:** an operation that appears indivisible to other threads and participates in the C++ memory model.
- **Invariant:** a rule that must remain true, such as “available quantity never becomes negative.”
- **Happens-before:** an ordering relationship that makes one thread's actions visible to another under the C++ memory model.

## Interview template

When asked how to make a data structure thread-safe, answer in this order:

1. Identify every shared field.
2. State the invariant that must never break.
3. Group the read/check/write steps that must be one atomic operation.
4. Choose the simplest lock that protects those fields.
5. Acquire it with RAII and keep the critical section short.
6. Define shutdown and object lifetime: who joins the threads and when can the object die?
7. Discuss contention only after correctness: sharding, a read/write lock, or lock-free code are optimizations, not defaults.

Example: an order execution must check quantity and subtract quantity under the same lock. Two separate locks would allow two traders to both observe the same old quantity.

## What this course does not pretend to cover

C++ is enormous. This course covers the practical core for systems, backend, and trading-style interviews. It does not replace studying algorithms, operating systems, networking, databases, CPU caches, profiling, or the exact C++ standard library used by a target company. Advanced topics such as lock-free reclamation, coroutines, executors, and custom allocators should come after these foundations.
