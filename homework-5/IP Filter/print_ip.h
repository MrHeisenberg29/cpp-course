#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <type_traits>


template <typename T>
typename std::enable_if<std::is_integral<T>::value, void>::type
print_ip(T value) 
{
    for (int i = sizeof(T) - 1; i >= 0; --i) 
    {
        std::cout << ((value >> (i * 8)) & 0xFF);
        if (i > 0) std::cout << ".";
    }
    std::cout << "\n";
}

template <typename T>
typename std::enable_if<std::is_same<T, std::string>::value, void>::type
print_ip(const T& value) 
{
    std::cout << value << "\n";
}

template <typename T>
struct is_vector_or_list : std::false_type {};

template <typename T, typename Alloc>
struct is_vector_or_list<std::vector<T, Alloc>> { static const bool value = true; };


template <typename T, typename Alloc>
struct is_vector_or_list<std::list<T, Alloc>> { static const bool value = true; };

template <typename T>
typename std::enable_if<is_vector_or_list<T>::value, void>::type
print_ip(const T& container) 
{
    bool first = true;
    for (const auto& item : container) 
    { 
        if (!first) std::cout << ".";
        std::cout << item;
        first = false;
    }
    std::cout << "\n";
}