#include <cstddef>
#include <iostream>
#include <tuple>

template<typename T>
struct Deleter {
    /// Default constructor
    Deleter() noexcept = default;

    void operator()(T *__ptr) const {
        delete __ptr;
    }
};

template<typename T, typename MyDeleter = Deleter<T>>
class UniquePtr {
private:
    std::tuple<T *, MyDeleter> ptr;

public:
    explicit UniquePtr() : ptr() {
    }

    explicit UniquePtr(T *_ptr) : ptr(_ptr, MyDeleter()) {
    }

    UniquePtr(UniquePtr &&other) noexcept {
        std::get<0>(ptr) = other.release();
        get_deleter() = std::forward<MyDeleter>(other.get_deleter());
    }


    explicit UniquePtr(T *_ptr, MyDeleter _deleter) : ptr(_ptr, _deleter) {
    }

    UniquePtr &operator=(std::nullptr_t) noexcept {
        get_deleter()(ptr);
        return *this;
    }

    UniquePtr &operator=(UniquePtr &&other) noexcept {
        reset(other.release());
        get_deleter() = std::forward<MyDeleter>(other.get_deleter());
        return *this;
    }

    ~UniquePtr() noexcept {
        auto &__ptr = std::get<0>(ptr);
        if (__ptr != nullptr)
            get_deleter()(__ptr);
        __ptr = nullptr;
    }

    T &operator*() {
        return *std::get<0>(ptr);
    }

    T &operator*() const {
        return *std::get<0>(ptr);
    }

    T *operator->() const noexcept {
        return std::get<0>(ptr);
    }

    T *release() noexcept {
        T *tmp = std::get<0>(ptr);
        std::get<0>(ptr) = nullptr;
        return tmp;
    }

    void reset(T *_ptr) noexcept {
        std::swap(std::get<0>(ptr), _ptr);
        get_deleter()(_ptr);
    }

    void swap(UniquePtr &other) noexcept {
        std::swap(ptr, other.ptr);
    }

    T *get() const noexcept {
        return std::get<0>(ptr);
    }

    explicit operator bool() const noexcept {
        return std::get<0>(ptr) != nullptr;
    }

    MyDeleter &get_deleter() {
        return std::get<1>(ptr);
    }

    MyDeleter &get_deleter() const {
        return std::get<1>(ptr);
    }
};
