#include <iostream>
#include <memory>
#include <string>

struct Connection {
    explicit Connection(std::string name) : name_(std::move(name)) {
        std::cout << "Open " << name_ << '\n';
    }

    ~Connection() {
        // The destructor runs automatically when the object leaves its scope.
        // This is the important idea behind RAII: cleanup is tied to lifetime.
        std::cout << "Close " << name_ << '\n';
    }

    std::string name_;
};

void stack_example() {
    // Stack objects are normally automatic: this object is destroyed when the
    // function returns, even if we return early or an exception is thrown.
    Connection connection("stack connection");
    std::cout << "Using stack object\n";
}

void heap_example() {
    // make_unique creates an object dynamically and gives ownership to pointer.
    // No manual delete is needed. When pointer leaves scope, the object closes.
    auto pointer = std::make_unique<Connection>("heap connection");
    std::cout << "Using heap object\n";
}

int main() {
    stack_example();
    heap_example();
}
