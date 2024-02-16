# Type Traits

There are two types of meta functions:

- Type Meta functions: `ValueIdentity<T>::type` (in type_traits, one can use `_t`)
- Value Meta functions: `ValueIdentity<T>::value` (in type_traits, one can use `_v`)


## Common/Useful Functions


### `std::is_same`

```cpp
//example mimic of the implementation
template<typename T, typename F>
struct is_same<T, F> : std::false_type{};

template<typename T>
struct is_same<T, T> : std::true_type{};

template<typename T, typename F>
constexpr bool is_same_v = is_same<T, F>::value;

```

### `std::integral_constant`

```cpp
template<class T, T v>
struct inegral_constant {
    static constexpr T value = v;
    using value_type = T;
    using type = integral_constant<T, v>;
    
    constexpr operator value_type() const noexcept {
        return value;
    }
    constexpr value_type()() const noexcept {
        return value;
    }
};
```
### `std::bool_constant`

```cpp
template <bool, B>
using bool_constant = integral_constant<bool, B>;
using true_type = bool_constant<true>; // here B = true
using false_type = bool_constant<false>; // here B = false
```

### `std::is_void`

```cpp
template <typename T>
struct is_void : std::false_type {}; // this is the general case

// special cases
template <>
struct is_void<void> : std::true_type {};

// by using remove_cv, I can do this:
template<typename T>
struct is_void : std::is_same<void, typename std::remove_cv<T>::type>{};
...
```

### **CV qualifiers / Transformation Trait**
- `std::remove_cv<T>`
- `std::remove_const<T>`
- `std::remove_volatile<T>`

### Conditional

```cpp
template<bool Condition, typename T, typename F>
struct conditional : type_identity<T> {}; // True

template<typename T, typename F>
struct conditional<false, T, F> : type_identity<F>{}; // False (specialization)
```


## SFINAE 