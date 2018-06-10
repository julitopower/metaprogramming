#ifndef TYPE_LIST_HPP
#define TYPE_LIST_HPP

#include <type_traits>

template <typename... TN>
class TypeList {
public:
    using type = TypeList;
    static constexpr std::size_t size() {
        return sizeof...(TN);
    }
};

////////////////////////////////////////////////////////////////////////////////
// Get Type at idx N
////////////////////////////////////////////////////////////////////////////////
template<std::uint8_t N, typename T>
class type_at {
};

template<std::uint8_t N, typename T, typename...TN>
class type_at<N, TypeList<T, TN...>> {
 public:
    using type = typename type_at<N - 1, TypeList<TN...>>::type;
};

template<typename T, typename...TN>
class type_at<0, TypeList<T, TN...>> {
 public:
    using type = T;
};
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Determine if 2 types are the same. Could have used std::is_same, but this
// is better for educational purposes.
////////////////////////////////////////////////////////////////////////////////
template<typename T1, typename T2>
class is_same_type : public std::false_type {};

template<typename T>
class is_same_type<T, T> : public std::true_type {};
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// If
////////////////////////////////////////////////////////////////////////////////
template<bool, typename T1, typename T2>
class if_t {
public:
    using type = T2;
};

template<typename T1, typename T2>
class if_t<true, T1, T2> {
public:
    using type = T1;
};

////////////////////////////////////////////////////////////////////////////////
// TypeList contains type.
////////////////////////////////////////////////////////////////////////////////
template<typename T, typename L>
class contains {
public:
    static constexpr bool value = false;
};

template<typename T, typename T1, typename... TN>
class contains<T, TypeList<T1, TN...>> {
 public:
    static constexpr bool value =
        if_t<is_same_type<T, T1>::value,
             std::true_type,
             contains<T, TypeList<TN...>>>::type::value;
};
////////////////////////////////////////////////////////////////////////////////

#endif // TYPE_LIST_HPP
