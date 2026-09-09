#include <memory>
#include <mutex>

std::shared_ptr<int> g_ptr;
std::mutex g_mutex;

void threadA() {
    {
        std::lock_guard<std::mutex> lock(g_mutex);
        g_ptr = std::make_shared<int>(100);
    }

    // Later, remove the shared pointer. The object remains alive while threadB
    // still owns its local copy.
    std::lock_guard<std::mutex> lock(g_mutex);
    g_ptr.reset();
}

void threadB() {
    std::shared_ptr<int> local_ptr;
    {
        std::lock_guard<std::mutex> lock(g_mutex);
        local_ptr = g_ptr;
    }

    if (local_ptr) {
        int value = *local_ptr;
        // Use value...
    }
}

void threadC(){
    {
        std::lock_guard<std::mutex> lock(g_mutex);
        g_ptr = std::make_shared<int>(200);
    }
}