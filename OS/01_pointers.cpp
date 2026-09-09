#include <iostream>
#include <memory>

struct Order {
    int quantity;
};

void raw_pointer_demo() {
    int price = 100;
    int* view = &price; // Non-owning pointer: price is still owned by this scope.
    *view = 101;
    std::cout << "price through raw pointer: " << price << '\n';
}

void ownership_demo() {
    auto single_owner = std::make_unique<Order>(Order{10});
    std::cout << "unique_ptr quantity: " << single_owner->quantity << '\n';

    auto another_owner = std::move(single_owner);
    std::cout << "ownership moved: " << another_owner->quantity << '\n';

    auto first_share = std::make_shared<Order>(Order{20});
    auto second_share = first_share;
    first_share->quantity = 25;
    std::cout << "shared value: " << second_share->quantity << '\n';

    std::weak_ptr<Order> observer = second_share;
    if (auto temporary_owner = observer.lock()) {
        std::cout << "weak_ptr observed: " << temporary_owner->quantity << '\n';
    }
}

int main() {
    raw_pointer_demo();
    ownership_demo();

