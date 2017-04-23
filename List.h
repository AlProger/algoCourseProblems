#include <cstddef>
#include <iterator>

using T = int;

class List {
/// Nodes
 public:
    class Node {
     public:
        T data;
        Node *next;
        Node *prev;

     public:
        Node(Node *next_, Node *prev_) : next(next_), prev(prev_) {
            prev->next = this;
            next->prev = this;
        }

        Node(const T &data, Node *next, Node *prev)
                : data(data), next(next), prev(prev) {
            prev->next = this;
            next->prev = this;
        }

        ~Node() {
            prev->next = next;
            next->prev = prev;
        }
    };
///

/// Iterators
 public:
    class Iterator : public std::iterator<std::bidirectional_iterator_tag, T> {
     public:
        Node *current;

     public:
        Iterator(Node *node) : current(node) {}

        bool operator==(Iterator const &other) const { return current == other.current; }

        bool operator!=(Iterator const &other) const { return !(*this == other); }

        Iterator &operator++() {
            current = current->next;
            return *this;
        }

        Iterator &operator--() {
            current = current->prev;
            return *this;
        }

        Iterator operator++(int) {
            Iterator result(*this);
            ++(*this);
            return result;
        }

        Iterator operator--(int) {
            Iterator result(*this);
            --(*this);
            return result;
        }

        T &operator*() const { return static_cast<Node *>(current)->data; }

        T *operator->() const { return &(static_cast<Node *>(current)->data); }
    };
///

/// list
 private:
    Node sentinel;
    size_t size_ = 0;

 public:
    List() : sentinel(&sentinel, &sentinel) {}

    void push_back(const T &_data) {
        new Node(_data, &sentinel, sentinel.prev);
        ++size_;
    }

    void push_front(const T &_data) {
        new Node(_data, sentinel.next, &sentinel);
        ++size_;
    }

    void pop_back() {
        if (size_ > 0) {
            delete sentinel.prev;
            --size_;
        }
    }

    void pop_front() {
        if (size_ > 0) {
            delete sentinel.next;
            --size_;
        }
    }

    size_t size() const {
        return size_;
    }

    Iterator begin() { return Iterator(sentinel.next); }

    Iterator end() { return Iterator(&sentinel); }

    bool empty() const {
        return size_ == 0;
    }

    ~List() {
        Node *tmp = nullptr;
        for (Node *loop = sentinel.next; loop != &sentinel; loop = tmp) {
            tmp = loop->next;
            delete loop;
        }
    }
};
