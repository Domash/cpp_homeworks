#include <type_traits>
#include <iostream>


#define SETTER(type, name)                      \
    void set_##name(type value) {               \
        using T = type;                         \
        using V = decltype(name);               \
                                                \
        static_assert(                          \
            std::is_fundamental<T>::value,      \
            "Type must be primitive"            \
        );                                      \
        static_assert(                          \
            std::is_fundamental<V>::value,      \
            "Type must be primitive"            \
        );                                      \
        static_assert(                          \
            std::is_same<T, V>::value,          \
            "Types must be same"                \
        );                                      \
        this -> name = value;                   \
    }

#define GETTER(type, name)                      \
    type get_##name() const {         \
        using T = type;                         \
        using V = decltype(name);               \
                                                \
        static_assert(                          \
            std::is_fundamental<T>::value,      \
            "Type must be primitive"            \
        );                                      \
        static_assert(                          \
            std::is_fundamental<V>::value,      \
            "Type must be primitive"            \
        );                                      \
        static_assert(                          \
            std::is_same<T, V>::value,          \
            "Types must be same"                \
        );                                      \
        return name;                            \
    }

class Text {
public:

    Text()  = default;
    ~Text() = default;

    SETTER(std::size_t, number);
    GETTER(std::size_t, number);

private:

    std::string text;
    std::size_t number;
};

signed main() {

    const auto x = new Text();

    x -> set_number(5);
    std::cout << x -> get_number() << std::endl;

    return 0;
}
