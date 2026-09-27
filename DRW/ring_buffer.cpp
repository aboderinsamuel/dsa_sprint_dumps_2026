#include <array>
#include <cstddef> // this is for std::size_t
#include <optional> // this is for std::optional

template <typename T, std::size_t N> // N is the size of the buffer
class  RingBuffer{
    static_assert(N > 1 && (N & (N - 1)) == 0, "N must be a power of 2 and greater than 1"); // N must be a power of 2 and greater than 1
    std::array<T, N> buf_{}; // the buffer
    std::size_t head_ = 0; // the index of the head of the buffer
    std::size_t tail_ = 0; // the index of the tail of the buffer

public:
    bool empty() const { return head_ == tail_; } // check if the buffer is empty
    bool full() const {return (head_ + 1) % N == tail_; } // check if the buffer is full

};