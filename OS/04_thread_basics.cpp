#include <iostream>
#include <thread>
#include <vector>

void print_work(int worker_id) {
    std::cout << "Worker " << worker_id << " is running\n";
}

int main() {
    // Constructing std::thread starts the function immediately.
    std::thread first_worker(print_work, 1);

    // join means: wait for this thread to finish before continuing.
    // A joinable thread must be joined or detached before its destructor runs.
    first_worker.join();

    std::vector<std::thread> workers;
    for (int worker_id = 2; worker_id <= 4; ++worker_id) {
        workers.emplace_back(print_work, worker_id);
    }

    // Joining every worker makes sure main does not finish while they use data
    // owned by main. This is usually safer than detach().
    for (auto& worker : workers) {
        worker.join();
    }

    // detach lets a thread run independently. It is easy to create a lifetime
    // bug, because the owner no longer knows when the thread finishes. Avoid it
    // for normal request work unless you have an explicit lifetime design.
}
