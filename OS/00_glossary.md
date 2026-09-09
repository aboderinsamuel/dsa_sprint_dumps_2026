# C++ Glossary: Simple First, Technical Second

Use this before reading the `.cpp` lessons. For every word, learn three things:

1. What it means in everyday language.
2. What it means technically in C++.
3. What a small example looks like.

## Program and memory basics

### Process

**Simple:** A running program.

**Technical:** An operating-system resource container with its own virtual address space, threads, and resources such as file handles.

**Example:** Running `order_book.exe` creates a process. That process may contain several worker threads.

### Thread

**Simple:** A path of work that can run independently.

**Technical:** A flow of execution inside a process. Threads in one process share memory, which makes communication easy but creates synchronization problems.

```cpp
std::thread worker([] { /* work runs on another thread */ });
worker.join();
```

### Stack

**Simple:** Fast, automatic storage for local variables.

**Technical:** Each thread has a stack used for function calls and local objects. Objects usually die automatically when their scope ends.

```cpp
void example() {
    int price = 100; // local object; destroyed when example returns
}
```

### Heap

**Simple:** Storage used for objects whose lifetime you want to manage dynamically.

**Technical:** Dynamically allocated storage obtained through `new` or, preferably, an allocation helper such as `std::make_unique`.

```cpp
auto order = std::make_unique<Order>(); // Order is dynamically allocated
```

### Scope

**Simple:** The region of code where a name exists.

**Technical:** A block delimited by `{}` or a function/class/namespace region. Automatic objects are destroyed when their scope ends.

```cpp
{
    int value = 42;
} // value no longer exists here
```

### Lifetime

**Simple:** The time between an object being created and destroyed.

**Technical:** Using an object outside its lifetime is undefined behavior, even if an old pointer still contains its former address.

## Pointers and ownership

### Address

**Simple:** The location of an object in memory.

```cpp
int value = 42;
int* pointer = &value; // & means "address of"
```

### Pointer

**Simple:** A variable that stores an address.

**Technical:** An object of type `T*` that may point to a `T`, point to `nullptr`, or be invalid if the pointed-to object no longer exists.

```cpp
int* pointer = &value;
*pointer = 50; // * means "object at this address"
```

### `nullptr`

**Simple:** A pointer value meaning “points to no object.”

**Technical:** The type-safe null pointer literal introduced in modern C++. Always prefer it over `0` or `NULL`.

```cpp
int* pointer = nullptr;
if (pointer != nullptr) {
    std::cout << *pointer;
}
```

The check and use are not automatically safe if another thread can change or destroy the pointer between them.

### Reference

**Simple:** Another name for an existing object.

**Technical:** An alias that must be bound during initialization. It is not nullable and does not express ownership.

```cpp
int value = 10;
int& alias = value;
alias = 20; // value is now 20
```

### Raw pointer

**Simple:** A pointer with no automatic ownership rules.

**Technical:** `T*` does not tell you whether the pointer owns the object. It is often best used as a non-owning view into an object owned elsewhere.

### `unique_ptr`

**Simple:** One owner responsible for cleanup.

**Technical:** A move-only RAII smart pointer. Its object is destroyed automatically when the pointer dies, unless ownership is moved.

```cpp
auto first = std::make_unique<int>(10);
auto second = std::move(first); // second owns it; first is empty
```

### `shared_ptr`

**Simple:** Several owners can share one object.

**Technical:** Reference-counted shared ownership. The object is destroyed when the last owning `shared_ptr` is destroyed or reset.

```cpp
auto first = std::make_shared<int>(10);
auto second = first; // both own the same int
```

The reference count is synchronized, but the `int` or class fields are not automatically protected from simultaneous modification.

### `weak_ptr`

**Simple:** An observer that does not keep an object alive.

**Technical:** A non-owning link to an object managed by `shared_ptr`. Call `lock()` to attempt to obtain a temporary owning `shared_ptr`.

```cpp
std::weak_ptr<int> observer = first;
if (auto owner = observer.lock()) {
    std::cout << *owner;
}
```

### Ownership

**Simple:** Responsibility for deciding when an object is destroyed.

**Technical:** A design contract. `unique_ptr` expresses one owner; `shared_ptr` expresses shared ownership; a raw pointer usually expresses no ownership unless documented otherwise.

## Resource management

### RAII

**Simple:** Put cleanup in an object's destructor so cleanup happens automatically.

**Technical:** Resource Acquisition Is Initialization. A resource is acquired by a constructor and released by the destructor, including when an exception or early return occurs.

```cpp
{
    std::lock_guard<std::mutex> lock(mutex); // acquire lock
} // destructor releases lock
```

### Destructor

**Simple:** Cleanup code that runs when an object dies.

**Technical:** A special member function named `~Type()`. It releases owned resources and runs automatically for normal scope exit and stack unwinding.

### Copy

**Simple:** Make a second independent value.

**Technical:** Copy construction or copy assignment duplicates the source's value. For a class owning a raw resource, a careless copy can cause double deletion.

### Move

**Simple:** Transfer resources instead of duplicating them.

**Technical:** Move construction or move assignment transfers ownership from a source object, which remains valid but is usually empty or changed.

```cpp
auto destination = std::move(source);
```

### Rule of 0/3/5

**Simple:** Let the standard library manage resources whenever possible.

**Technical:** Rule of 0: define none of the special members. Rule of 3: if you define destructor, copy constructor, or copy assignment, you probably need all three. Rule of 5 adds move constructor and move assignment.

## Synchronization

### Shared state

**Simple:** Data that multiple threads can access.

```cpp
int balance; // shared if several threads use it
```

### Data race

**Simple:** Two threads access the same memory at the same time, and at least one writes, without proper synchronization.

**Technical:** A data race is undefined behavior in C++. The compiler is allowed to assume it never happens.

### Race condition

**Simple:** The answer changes depending on which thread gets there first.

**Technical:** A timing-dependent program behavior. A race condition can be a design bug even when the individual memory accesses are synchronized.

### Critical section

**Simple:** The smallest piece of shared work that must not be interrupted by another worker.

```cpp
std::lock_guard<std::mutex> lock(mutex);
// check + update the shared order book here
```

### Mutex

**Simple:** A lock that lets only one thread enter a protected region at a time.

**Technical:** `std::mutex` provides mutual exclusion. A thread locks it, accesses protected state, and unlocks it.

```cpp
std::mutex mutex;
std::lock_guard<std::mutex> lock(mutex);
++shared_counter;
```

A mutex protects access. It does not automatically manage object lifetime or make unrelated data safe.

### `lock_guard`

**Simple:** The easiest safe way to hold a mutex for one scope.

**Technical:** A non-copyable RAII wrapper that locks in its constructor and unlocks in its destructor. It cannot be manually unlocked.

### `unique_lock`

**Simple:** A more flexible lock holder.

**Technical:** An RAII lock wrapper that can be unlocked and relocked, moved, and passed to a condition variable.

```cpp
std::unique_lock<std::mutex> lock(mutex);
lock.unlock();
```

### `scoped_lock`

**Simple:** Lock several mutexes safely together.

**Technical:** `std::scoped_lock` uses a deadlock-avoidance algorithm when locking multiple mutexes.

```cpp
std::scoped_lock lock(first_mutex, second_mutex);
```

### Deadlock

**Simple:** Threads wait forever for one another.

**Technical:** A cycle of waiting. Thread A owns lock 1 and waits for lock 2; thread B owns lock 2 and waits for lock 1.

**Prevention:** Always acquire multiple locks in a consistent order, or use `std::scoped_lock`.

### Starvation

**Simple:** A thread keeps waiting because other threads repeatedly get the resource first.

**Technical:** A liveness failure where a thread makes no progress even though the system as a whole is active.

### Livelock

**Simple:** Threads are active but keep reacting to one another without completing work.

**Technical:** Threads repeatedly change state to avoid conflict, but no useful progress occurs.

### Invariant

**Simple:** A rule that must always remain true.

```text
available quantity >= 0
```

**Technical:** A property preserved before and after every operation. The order-book check and subtraction must be protected together to preserve the invariant.

## Waiting and communication

### Condition variable

**Simple:** A way for a thread to sleep until work or a state change may be available.

**Technical:** `std::condition_variable` coordinates with a `std::unique_lock`. The waiting thread releases the mutex while asleep and reacquires it before checking the predicate.

```cpp
condition.wait(lock, [&] { return !queue.empty() || closed; });
```

Always use a predicate or a loop because wakeups can be spurious and because another thread may consume the condition first.

### Notify

**Simple:** Tell sleeping threads to check again.

**Technical:** `notify_one()` wakes one waiter; `notify_all()` wakes every waiter. Notification does not itself prove the condition is true.

### Producer/consumer

**Simple:** Producers create work; consumers process work.

**Technical:** A shared queue plus a mutex and condition variables. Producers wait when the queue is full; consumers wait when it is empty.

### Shutdown

**Simple:** A deliberate signal that no more work will arrive.

**Technical:** A shared `closed` or `stop_requested` state, protected by synchronization, followed by notifications and thread joins.

## Atomics and visibility

### Atomic

**Simple:** An operation that other threads see as one indivisible operation.

**Technical:** `std::atomic<T>` provides race-free operations on supported types. It does not make a group of several operations automatically atomic.

```cpp
std::atomic<int> completed{0};
completed.fetch_add(1);
```

Use a mutex when you need to protect an invariant involving multiple fields or steps.

### Memory ordering

**Simple:** Rules for when one thread is guaranteed to see another thread's writes.

**Technical:** C++ atomic operations use memory-order options. `seq_cst` is the strongest and easiest to reason about. Acquire/release can provide synchronization with weaker ordering. Relaxed provides atomicity but not general visibility ordering.

### Acquire/release

**Simple:** One thread publishes data; another thread is guaranteed to see it after observing the publication flag.

**Technical:** A release store synchronizes with an acquire load that reads that value, creating a happens-before relationship for prior writes.

### Happens-before

**Simple:** A rule proving that one action is ordered before another.

**Technical:** The C++ memory model uses happens-before to define when side effects become visible and to prevent certain reorderings.

## Thread results and architecture

### `join`

**Simple:** Wait for a thread to finish.

**Technical:** `join()` synchronizes the caller with completion of the target thread. A joinable thread must be joined or detached before its `std::thread` is destroyed.

### `detach`

**Simple:** Let a thread run independently.

**Technical:** The `std::thread` object gives up ownership of the running thread. You must guarantee that every referenced object outlives the detached thread. This is easy to get wrong.

### `future`

**Simple:** A box containing a result that will be ready later.

**Technical:** `std::future<T>::get()` waits for the asynchronous result and rethrows an exception from the worker if one occurred.

### `promise`

**Simple:** A worker's way to place a value or exception into a future.

**Technical:** `std::promise<T>` sets the shared state consumed by a matching `std::future<T>`.

### `async`

**Simple:** Ask C++ to run a callable and give you a future.

**Technical:** `std::async` manages an asynchronous result; `std::launch::async` requests execution on another thread.

### Thread pool

**Simple:** A reusable group of worker threads that process queued jobs.

**Technical:** A queue protected by a mutex and condition variable, plus workers that repeatedly wait, pop a task, execute it, and stop during shutdown.

### `shared_mutex`

**Simple:** Many readers may enter together, but writers need exclusive access.

**Technical:** `std::shared_mutex` supports `std::shared_lock` for readers and `std::unique_lock` for writers. It helps only when reads dominate and contention is measured.

### Thread-safe

**Simple:** Using an object from multiple threads does not break its rules.

**Technical:** Every shared access is synchronized appropriately, object lifetime is valid, and compound invariants are protected as one operation.

## Interview sentence to memorize

> I first identify the shared state and its invariant. Then I make the check and update that preserve the invariant one synchronized operation, using RAII to manage the lock. Finally, I define thread shutdown and object lifetime before discussing optimizations such as sharding or lock-free structures.
