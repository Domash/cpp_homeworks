#include <iostream>
#include <memory>

template <class Type>
class NonCopyable {
public:

    NonCopyable(const NonCopyable& ) = delete;
    Type& operator = (const Type& )  = delete;

protected:

    NonCopyable()  = default;
    ~NonCopyable() = default;

};

template <class Type, class Deleter = std::default_delete<Type>>
class unique_ptr : private NonCopyable<Type> {
public:

    unique_ptr() {
        data_ = std::make_pair(nullptr, Deleter());
    }

    unique_ptr(Type* pointer, Deleter deleter = Deleter()) {
        data_.first  = pointer;
        data_.second = deleter;
        pointer      = nullptr;
    }

    unique_ptr(unique_ptr&& other) {
        data_.first  = std::move(other.data_.first);
        data_.second = std::move(other.data_.second);
        other.data_.first = nullptr;
    }

    ~unique_ptr() {
        this -> get_deleter()(data_.first);
    }

    unique_ptr& operator = (unique_ptr&& other) {
        std::swap(data_, other.data_);
        return *this;
    }

    unique_ptr& operator = (std::nullptr_t other) {
        this -> get_deleter()(data_.first);
        data_.first = other;
        return *this;
    }

    Type& operator * () {
        return *data_.first;
    }

    const Type& operator * () const {
        return *data_.first;
    }

    Type* operator -> () const {
        return data_.first;
    }

    Type* release() const {
        Type* pointer = data_.first;
        data_.first   = nullptr;
        return pointer;
    }

    void reset(Type* pointer) {
        this -> get_deleter()(data_.first);
        data_.first = pointer;
        pointer = nullptr;
    }

    void swap(unique_ptr& other) {
        std::swap(data_, other.data_);
    }

    Type* get() const {
        return data_.first;
    }

    Deleter& get_deleter() {
        return data_.second;
    }

    const Deleter& get_deleter() const {
        return data_.second;
    }

    explicit operator bool() const {
        return data_.first != nullptr;
    }

private:

    std::pair<Type*, Deleter> data_;

};

signed main() {

    unique_ptr<int> x;
    unique_ptr<int>(new int(1));

}