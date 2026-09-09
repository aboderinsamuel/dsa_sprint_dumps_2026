#include <iostream>
#include <string>
#include <utility>

class Message {
public:
    explicit Message(std::string text) : text_(std::move(text)) {}

    Message(const Message& other) : text_(other.text_) {
        std::cout << "Copy constructor\n";
    }

    Message& operator=(const Message& other) {
        std::cout << "Copy assignment\n";
        if (this != &other) {
            text_ = other.text_;
        }
        return *this;
    }

    Message(Message&& other) noexcept : text_(std::move(other.text_)) {
        std::cout << "Move constructor\n";
    }

    Message& operator=(Message&& other) noexcept {
        std::cout << "Move assignment\n";
        if (this != &other) {
            text_ = std::move(other.text_);
        }
        return *this;
    }

    const std::string& text() const { return text_; }

private:
    std::string text_;
};

Message make_message() {
    // Returning by value can use move construction or copy elision.
    return Message("created in a function");
}

int main() {
    Message first("hello");
    Message copied = first; // Copy: both objects contain independent text.
    Message moved = std::move(first); // Move: resources transfer from first.
    Message result = make_message();

    std::cout << "Copied: " << copied.text() << '\n';
    std::cout << "Moved: " << moved.text() << '\n';
    std::cout << "Result: " << result.text() << '\n';
}
