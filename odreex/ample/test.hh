/**
 * Copyright (C) 2013, George Makrydakis <irrequietus@gmail.com>
 * 
 * This file is part of odreex.
 * odreex is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * odreex is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with odreex. If not, see <http://www.gnu.org/licenses/>.
 * 
 */

#ifndef _ODREEX_AMPLE_TEST_HH_
#define _ODREEX_AMPLE_TEST_HH_

#define ample_vldt_(t) \
    static constexpr char const * showln() noexcept \
    { return t ; }

# ifdef AMPLE_PRINTLN_LIM
#    if AMPLE_PRINTLN_LIM > 255
#        define AMPLE_PRINTLN_LIM 52
#    endif
# else
#    define AMPLE_PRINTLN_LIM 52
# endif

#ifdef USE_ANSI_COLORS
#define ample_printf_(i, sz, N) \
    printf( "\033[1;37m[%06zu]\033[0m: %s | %s |: \033[34m%s%s\033[0m\n" \
          , i \
          , result[ i ] ? "\033[36mpass\033[0m" : "\033[31mfail\033[0m" \
          , output[ i ] ? "\033[1;36mpass\033[0m" : "\033[1;31mfail\033[0m" \
          , cbuf \
          , sz <= N ? "" : "..." )
#else
#define ample_printf_(i, sz, N) \
    printf( "[%06zu]: %s | %s |: %s%s\n" \
          , i \
          , result[ i ] ? "pass" : "fail" \
          , output[ i ] ? "pass" : "fail" \
          , cbuf \
          , sz <= N ? "" : "..." )
#endif

/**
 * NOTE: Testing mechanism fundamentals for the various odreex::ample template
 * metaprogramming constructs.
 **/

#include <cstdio>
#include <cstring>
#include <type_traits>
#include <algorithm>

namespace odreex {
namespace ample {
namespace test {

struct as_passed {};
struct as_failed {};
struct as_output {};
struct as_expect {};
struct as_result {};
struct as_showln {};

/* class template for types that must be "matched" */
template<typename Type_X, typename Type_Y>
struct types_match 
    : std::integral_constant<bool, std::is_same<Type_X, Type_Y>::value >
{};

/* class template for values in types that must be "matched" */
template<typename Type_X, typename Type_Y>
struct values_match
    : std::integral_constant<bool, Type_X::value == Type_Y::value>
{};

/* the default test class templates providing details */

template<typename Type_A, typename Type_B, bool Expected_B = true>
struct vldt_types : types_match<Type_A, Type_B> {
    
    static constexpr bool expected() {
        return Expected_B;
    }
    
    static constexpr bool result() {
        return types_match<Type_A, Type_B>::value;
    }
    
    static constexpr bool output() {
        return types_match<Type_A, Type_B>::value == Expected_B;
    }
    
    static constexpr char const * showln() {
        return "default odreex::ample::test validation showln";
    }
};

template<typename Type_A, typename Type_B, bool Expected_B = true>
struct vldt_values : values_match<Type_A, Type_B> {
    
    static constexpr bool expected() {
        return Expected_B;
    }
    
    static constexpr bool result() {
        return values_match<Type_A, Type_B>::value;
    }
    
    static constexpr bool output() {
        return values_match<Type_A, Type_B>::value == Expected_B;
    }
    
    static constexpr char const * showln() {
        return "default odreex::ample::test validation showln";
    }
};

/*NOTE: a wrapper class that is a temporary utility */
template<std::size_t... N>
struct wrap_
{};

/* NOTE: constexpr arrays seem to be having some issues with clang++ (3.3.x) so
 * we will be using the "old" way of doing things until this thing gets fixed.
 * Notice that g++ has no problem with either style.
 */
template<typename... T>
struct check_all {
    
    template<typename, typename, typename, typename, std::size_t, bool Casc_B>
    struct check_impl;
    
    template< typename X
            , typename... Xn
            , std::size_t... A
            , std::size_t... B
            , std::size_t... C
            , std::size_t N
            , bool Casc_B >
    struct check_impl< wrap_<A...>
                     , wrap_<B...>
                     , wrap_<C...>
                     , check_all<X, Xn...>
                     , N
                     , Casc_B >
         : std::conditional< X::output() == Casc_B
                           , check_impl< wrap_<A..., N>
                                       , wrap_<B...>
                                       , wrap_<C..., N>
                                       , check_all<Xn...>
                                       , N + 1
                                       , Casc_B >
                           , check_impl< wrap_<A...>
                                       , wrap_<B..., N>
                                       , wrap_<C..., N>
                                       , check_all<Xn...>
                                       , N + 1
                                       , Casc_B >>::type
    {};
    
    template< std::size_t... A
            , std::size_t... B
            , std::size_t... C
            , std::size_t N
            , bool Casc_B >
    struct check_impl< wrap_<A...>
                     , wrap_<B...>
                     , wrap_<C...>
                     , check_all<>
                     , N
                     , Casc_B > {
        static std::size_t const    passed_total = sizeof...(A);
        static std::size_t const    failed_total = sizeof...(B);
        static std::size_t const    checks_total = sizeof...(T);
        static std::size_t const    passed[sizeof...(A)];
        static std::size_t const    failed[sizeof...(B)];
        static std::size_t const    shnoop[sizeof...(C)];
        static char const *         showln[sizeof...(T)];
        static bool const           output[sizeof...(T)];
        static bool const           result[sizeof...(T)];
        static bool const           expect[sizeof...(T)];
    };
    
public:
    template<bool B>
    using apply = check_impl<wrap_<>, wrap_<>, wrap_<>, check_all<T...>, 0, B>;
};

template<typename... T>
template< std::size_t... A
        , std::size_t... B
        , std::size_t... C
        , std::size_t N
        , bool Cb >
std::size_t const check_all<T...>
    ::check_impl< wrap_<A...>
                , wrap_<B...>
                , wrap_<C...>
                , check_all<>
                , N
                , Cb >::passed[] = {
    A...
};

template<typename... T>
template< std::size_t... A
        , std::size_t... B
        , std::size_t... C
        , std::size_t N
        , bool Cb >
std::size_t const check_all<T...>
    ::check_impl< wrap_<A...>
                , wrap_<B...>
                , wrap_<C...>
                , check_all<>
                , N
                , Cb >::failed[] = {
    B...
};

template<typename... T>
template< std::size_t... A
        , std::size_t... B
        , std::size_t... C
        , std::size_t N
        , bool Cb >
bool const check_all<T...>
    ::check_impl< wrap_<A...>
                , wrap_<B...>
                , wrap_<C...>
                , check_all<>
                , N
                , Cb >::result[] = {
    T::result()...
};

template<typename... T>
template< std::size_t... A
        , std::size_t... B
        , std::size_t... C
        , std::size_t N
        , bool Cb >
bool const check_all<T...>
    ::check_impl< wrap_<A...>
                , wrap_<B...>
                , wrap_<C...>
                , check_all<>
                , N
                , Cb >::output[] = {
    T::output()...
};

template<typename... T>
template< std::size_t... A
        , std::size_t... B
        , std::size_t... C
        , std::size_t N
        , bool Cb >
bool const check_all<T...>
    ::check_impl< wrap_<A...>
                , wrap_<B...>
                , wrap_<C...>
                , check_all<>
                , N
                , Cb >::expect[] = {
    T::expected()...
};

template<typename... T>
template< std::size_t... A
        , std::size_t... B
        , std::size_t... C
        , std::size_t N
        , bool Cb >
char const * check_all<T...>
    ::check_impl< wrap_<A...>
                , wrap_<B...>
                , wrap_<C...>
                , check_all<>
                , N
                , Cb >::showln[] = {
    T::showln()...
};

template<typename... T>
template< std::size_t... A
        , std::size_t... B
        , std::size_t... C
        , std::size_t N
        , bool Cb >
std::size_t const check_all<T...>
    ::check_impl< wrap_<A...>
                , wrap_<B...>
                , wrap_<C...>
                , check_all<>
                , N
                , Cb >::shnoop[] = {
    C...
};

template<bool Cascade_B, typename Check_T>
struct check : private Check_T::template apply<Cascade_B> {
private:
    using Check_T::template apply<Cascade_B>::passed;
    using Check_T::template apply<Cascade_B>::failed;
    using Check_T::template apply<Cascade_B>::output;
    using Check_T::template apply<Cascade_B>::result;
    using Check_T::template apply<Cascade_B>::expect;
    using Check_T::template apply<Cascade_B>::showln;
    using Check_T::template apply<Cascade_B>::shnoop;
    using Check_T::template apply<Cascade_B>::passed_total;
    using Check_T::template apply<Cascade_B>::failed_total;
    using Check_T::template apply<Cascade_B>::checks_total;
    
    static constexpr char const * at_(std::size_t const &i, as_failed) {
        return showln[failed[i]];
    }
    
    static constexpr char const * at_(std::size_t const &i, as_passed) {
        return showln[passed[i]];
    }
    
    static constexpr char const * at_(std::size_t const &i, as_showln) {
        return showln[i];
    }
    
    static constexpr std::size_t const * begin_(as_output) {
        return &output[0];
    }
    
    static constexpr std::size_t const * begin_(as_result) {
        return &result[0];
    }
    
    static constexpr std::size_t const * begin_(as_expect) {
        return &expect[0];
    }
    
    static constexpr std::size_t const * begin_(as_failed) {
        return &failed[0];
    }
    
    static constexpr std::size_t const * begin_(as_passed) {
        return &passed[0];
    }
    
    static constexpr std::size_t const * begin_(as_showln) {
        return &shnoop[0];
    }
    
    static constexpr std::size_t const * end_(as_output) {
        return &output[checks_total];
    }
    
    static constexpr std::size_t const * end_(as_result) {
        return &result[checks_total];
    }
    
    static constexpr std::size_t const * end_(as_expect) {
        return &expect[checks_total];
    }
    
    static constexpr std::size_t const * end_(as_failed) {
        return &failed[failed_total];
    }
    
    static constexpr std::size_t const * end_(as_passed) {
        return &passed[passed_total];
    }
    
    static constexpr std::size_t const * end_(as_showln) {
        return &shnoop[checks_total];
    }
    
public:
    template<typename Input_T = as_showln>
    static constexpr auto at(std::size_t const & i)
        -> decltype(at_(i, Input_T()))
    { return at_(i, Input_T()); }
    
    template<typename Input_T = as_showln>
    static constexpr auto begin()
        -> decltype(begin_(Input_T()))
    { return begin_(Input_T()); }
    
    template<typename Input_T = as_showln>
    static constexpr auto end()
        -> decltype(begin_(Input_T()))
    { return end_(Input_T()); }
    
    template<typename Input_T = as_showln>
    auto operator[](std::size_t const &i) const
      -> decltype(at_(i, Input_T()))
    { return at_(i, Input_T()); }
    
    static bool println(std::size_t const &i) {
        size_t sz(strlen(showln[i]))
             , cz(sz < AMPLE_PRINTLN_LIM ? sz : AMPLE_PRINTLN_LIM);
        char cbuf[AMPLE_PRINTLN_LIM + 1];
        std::copy_n(showln[i], cz, cbuf);
        cbuf[cz] = (char)0;
        ample_printf_(i, cz, AMPLE_PRINTLN_LIM);
        return result[i];
    }
};

} /* test */
} /* ample */
} /* odreex */

#undef ample_printf_ /* remove this macro */

#endif /* _ODREEX_AMPLE_TEST_HH_ */