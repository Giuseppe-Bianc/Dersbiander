#pragma once
#include <algorithm>     // for forward
#include <cstddef>       // for ptrdiff_t, nullptr_t, size_t
#include <memory>        // for shared_ptr, unique_ptr
#include <system_error>  // for hash
#include <type_traits>   // for enable_if_t, is_convertible, is_assignable
#include <utility>       // for declval

namespace dersbiander {

template <typename T>
concept Pointer = std::is_pointer_v<T>;

namespace details {

template <typename T, typename = void>
struct is_comparable_to_nullptr : std::false_type {};

template <typename T>
struct is_comparable_to_nullptr<T, std::enable_if_t<std::is_convertible_v<decltype(std::declval<T>() != nullptr), bool>>> : std::true_type {};

template <typename T>
using value_or_reference_return_t = std::conditional_t<
    sizeof(T) < 2 * sizeof(void *) && std::is_trivially_copy_constructible_v<T>, const T, const T &>;

}  // namespace details

using std::shared_ptr;
using std::unique_ptr;

template <Pointer T>
using owner = T;

template <class T> requires details::is_comparable_to_nullptr<T>::value
class not_null {
public:
    constexpr not_null(T u) noexcept(std::is_nothrow_move_constructible_v<T>) : ptr_(std::move(u)) {
        static_assert(ptr_ != nullptr);
    }

    template <typename U> requires std::is_convertible_v<U, T>
    constexpr not_null(const not_null<U> &other) noexcept(std::is_nothrow_move_constructible_v<T>)
        : not_null(other.get()) {}

    not_null(const not_null &other) = default;
    not_null &operator=(const not_null &other) = default;

    constexpr details::value_or_reference_return_t<T> get() const
        noexcept(noexcept(details::value_or_reference_return_t<T>{std::declval<T &>()})) {
        return ptr_;
    }

    constexpr operator T() const { return get(); }
    constexpr decltype(auto) operator->() const { return get(); }
    constexpr decltype(auto) operator*() const { return *get(); }

    not_null(std::nullptr_t) = delete;
    not_null &operator=(std::nullptr_t) = delete;

    not_null &operator++() = delete;
    not_null &operator--() = delete;
    not_null operator++(int) = delete;
    not_null operator--(int) = delete;
    not_null &operator+=(std::ptrdiff_t) = delete;
    not_null &operator-=(std::ptrdiff_t) = delete;
    void operator[](std::ptrdiff_t) const = delete;

private:
    T ptr_;
};

template <class T> requires details::is_comparable_to_nullptr<T>::value
auto make_not_null(T &&t) noexcept {
    return not_null<std::remove_cv_t<std::remove_reference_t<T>>>{std::forward<T>(t)};
}

template <class T, class U>
auto operator==(const not_null<T> &lhs, const not_null<U> &rhs) noexcept(noexcept(lhs.get() == rhs.get()))
    -> decltype(lhs.get() == rhs.get()) {
    return lhs.get() == rhs.get();
}

template <class T, class U>
auto operator!=(const not_null<T> &lhs, const not_null<U> &rhs) noexcept(noexcept(lhs.get() != rhs.get()))
    -> decltype(lhs.get() != rhs.get()) {
    return lhs.get() != rhs.get();
}

template <class T, class U>
auto operator<(const not_null<T> &lhs, const not_null<U> &rhs) noexcept(noexcept(std::less<>{}(lhs.get(), rhs.get())))
    -> decltype(std::less<>{}(lhs.get(), rhs.get())) {
    return std::less<>{}(lhs.get(), rhs.get());
}

template <class T, class U>
auto operator<=(const not_null<T> &lhs, const not_null<U> &rhs) noexcept(noexcept(std::less_equal<>{}(lhs.get(), rhs.get())))
    -> decltype(std::less_equal<>{}(lhs.get(), rhs.get())) {
    return std::less_equal<>{}(lhs.get(), rhs.get());
}

template <class T, class U>
auto operator>(const not_null<T> &lhs, const not_null<U> &rhs) noexcept(noexcept(std::greater<>{}(lhs.get(), rhs.get())))
    -> decltype(std::greater<>{}(lhs.get(), rhs.get())) {
    return std::greater<>{}(lhs.get(), rhs.get());
}

template <class T, class U>
auto operator>=(const not_null<T> &lhs, const not_null<U> &rhs) noexcept(noexcept(std::greater_equal<>{}(lhs.get(), rhs.get())))
    -> decltype(std::greater_equal<>{}(lhs.get(), rhs.get())) {
    return std::greater_equal<>{}(lhs.get(), rhs.get());
}

template <class T, class U> std::ptrdiff_t operator-(const not_null<T> &, const not_null<U> &) = delete;
template <class T> not_null<T> operator-(const not_null<T> &, std::ptrdiff_t) = delete;
template <class T> not_null<T> operator+(const not_null<T> &, std::ptrdiff_t) = delete;
template <class T> not_null<T> operator+(std::ptrdiff_t, const not_null<T> &) = delete;

template <class T, class U = decltype(std::declval<const T &>().get()),
          bool = std::is_default_constructible_v<std::hash<U>>>
struct not_null_hash {
    std::size_t operator()(const T &value) const { return std::hash<U>{}(value.get()); }
};

template <class T, class U>
struct not_null_hash<T, U, false> {
    not_null_hash() = delete;
    not_null_hash(const not_null_hash &) = delete;
    not_null_hash &operator=(const not_null_hash &) = delete;
};

}  // namespace dersbiander

namespace std {
template <class T> requires dersbiander::details::is_comparable_to_nullptr<T>::value
struct hash<dersbiander::not_null<T>> : dersbiander::not_null_hash<dersbiander::not_null<T>> {};
}

namespace dersbiander {

template <class T> requires dersbiander::details::is_comparable_to_nullptr<T>::value
class strict_not_null : public not_null<T> {
public:
    constexpr explicit strict_not_null(T u) : not_null<T>(std::move(u)) {}

    template <typename U> requires std::is_convertible_v<U, T>
    constexpr strict_not_null(const not_null<U> &other) : not_null<T>(other) {}

    template <typename U> requires std::is_convertible_v<U, T>
    constexpr strict_not_null(const strict_not_null<U> &other) : not_null<T>(other) {}

    strict_not_null(strict_not_null &&other) noexcept(std::is_nothrow_copy_constructible<T>::value) = default;
    strict_not_null(const strict_not_null &other) = default;
    strict_not_null &operator=(const strict_not_null &other) = default;
    strict_not_null &operator=(const not_null<T> &other) {
        not_null<T>::operator=(other);
        return *this;
    }
};

template <class T, class U> std::ptrdiff_t operator-(const strict_not_null<T> &, const strict_not_null<U> &) = delete;
template <class T> strict_not_null<T> operator-(const strict_not_null<T> &, std::ptrdiff_t) = delete;
template <class T> strict_not_null<T> operator+(const strict_not_null<T> &, std::ptrdiff_t) = delete;
template <class T> strict_not_null<T> operator+(std::ptrdiff_t, const strict_not_null<T> &) = delete;

template <class T> requires dersbiander::details::is_comparable_to_nullptr<T>::value
auto make_strict_not_null(T &&t) noexcept {
    return strict_not_null<std::remove_cv_t<std::remove_reference_t<T>>>{std::forward<T>(t)};
}

template <class T> not_null(T) -> not_null<T>;
template <class T> strict_not_null(T) -> strict_not_null<T>;

}  // namespace dersbiander

namespace std {
template <class T> requires dersbiander::details::is_comparable_to_nullptr<T>::value
struct hash<dersbiander::strict_not_null<T>> : dersbiander::not_null_hash<dersbiander::strict_not_null<T>> {};
}
