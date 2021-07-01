/**
 * Copyright (c) 2011-2021 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef LIBBITCOIN_SYSTEM_MATH_BITS_IPP
#define LIBBITCOIN_SYSTEM_MATH_BITS_IPP

#include <cstddef>
#include <limits>
#include <bitcoin/system/constants.hpp>
#include <bitcoin/system/math/sign.hpp>
#include <bitcoin/system/type_constraints.hpp>

namespace libbitcoin {
namespace system {

// complements

template <typename Integer, if_integer<Integer>>
constexpr Integer ones_complement(Integer value) noexcept
{
    return ~value;
}

template <typename Integer, if_integer<Integer>>
constexpr Integer twos_complement(Integer value) noexcept
{
    return add1(ones_complement(value));
}

// bits

template <typename Value, if_integer<Value>>
constexpr Value bit_lo()
{
    return to_int<Value>(true) << zero;
}

template <typename Value, if_integer<Value>>
constexpr Value bit_hi()
{
    // sub1 for size-to-index translation.
    return to_int<Value>(true) << sub1(width<Value>());
}

template <typename Value, if_integer<Value>>
constexpr Value bit_right(size_t offset)
{
    return bit_lo<Value>() << offset;
}

template <typename Value, if_integer<Value>>
constexpr Value bit_left(size_t offset)
{
    return bit_hi<Value>() >> offset;
}

template <typename Value, if_integer<Value>>
constexpr Value bit_all()
{
    return ones_complement<Value>(0);
}

// width

// Avoid sizeof as it is incorrect for non-itegral types, such as uintx.
// "For integer types, this is the number of bits not counting the sign
// bit and the padding bits (if any)"
// en.cppreference.com/w/cpp/types/numeric_limits/digits

template <typename Value, if_unsigned_integer<Value>>
constexpr size_t width(Value)
{
    return std::numeric_limits<Value>::digits;
}

template <typename Value, if_signed_integer<Value>>
constexpr size_t width(Value)
{
    return add1(std::numeric_limits<Value>::digits);
}

// set

template <typename Value, if_integer<Value>>
constexpr Value set_right(Value& target, size_t offset, bool state)
{
    // C++14: local variables allowed in constexpr.
    return state ? ((target |= bit_right<Value>(offset))) :
        ((target &= ones_complement(bit_right<Value>(offset))));
}

template <typename Value, if_integer<Value>>
constexpr Value set_right(const Value& target, size_t offset, bool state)
{
    // C++14: local variables allowed in constexpr.
    return state ? target | bit_right<Value>(offset) :
        target & ones_complement(bit_right<Value>(offset));
}

template <typename Value, if_integer<Value>>
constexpr Value set_left(Value& target, size_t offset, bool state)
{
    // C++14: local variables allowed in constexpr.
    return state ? ((target |= bit_left<Value>(offset))) :
        ((target &= ones_complement(bit_left<Value>(offset))));
}

template <typename Value, if_integer<Value>>
constexpr Value set_left(const Value& target, size_t offset, bool state)
{
    // C++14: local variables allowed in constexpr.
    return state ? target | bit_left<Value>(offset) :
        target & ones_complement(bit_left<Value>(offset));
}

// get

template <typename Value, if_integer<Value>>
constexpr bool get_right(Value value, size_t offset)
{
    return !is_zero(value & bit_right<Value>(offset));
}

template <typename Value, if_integer<Value>>
constexpr bool get_left(Value value, size_t offset)
{
    return !is_zero(value & bit_left<Value>(offset));
}

// mask

template <typename Value, if_integer<Value>>
constexpr Value mask_right(size_t bits)
{
    return bit_all<Value>() << bits;
}

template <typename Value, if_integer<Value>>
constexpr Value mask_right(Value& value, size_t bits)
{
    return ((value &= mask_right<Value>(bits)));
}

template <typename Value, if_integer<Value>>
constexpr Value mask_right(const Value& value, size_t bits)
{
    return value & mask_right<Value>(bits);
}

template <typename Value, if_integer<Value>>
constexpr Value mask_left(size_t bits)
{
    return bit_all<Value>() >> bits;
}

template <typename Value, if_integer<Value>>
constexpr Value mask_left(Value& value, size_t bits)
{
    return ((value &= mask_left<Value>(bits)));
}

template <typename Value, if_integer<Value>>
constexpr Value mask_left(const Value& value, size_t bits)
{
    return value & mask_left<Value>(bits);
}

// flag

template <typename Value, if_integer<Value>>
constexpr Value flag_right(size_t bits)
{
    return ones_complement(bit_all<Value>() << bits);
}

template <typename Value, if_integer<Value>>
constexpr Value flag_right(Value& value, size_t bits)
{
    return ((value |= flag_right<Value>(bits)));
}

template <typename Value, if_integer<Value>>
constexpr Value flag_right(const Value& value, size_t bits)
{
    return value | flag_right<Value>(bits);
}

template <typename Value, if_integer<Value>>
constexpr Value flag_left(size_t bits)
{
    return ones_complement(bit_all<Value>() >> bits);
}

template <typename Value, if_integer<Value>>
constexpr Value flag_left(Value& value, size_t bits)
{
    return ((value |= flag_left<Value>(bits)));
}

template <typename Value, if_integer<Value>>
constexpr Value flag_left(const Value& value, size_t bits)
{
    return value | flag_left<Value>(bits);
}

// rotate

// C++20: std::rotl/rotr can replace rotate_left/rotate_right.
// C++20: std::rotl/rotr can replace rotate_left/rotate_right.

template <typename Value, if_integer<Value>>
constexpr Value rotate_right(Value& value, size_t shift)
{
    // C++14: local variables allowed in constexpr.
    constexpr auto bits = width<Value>();
    return ((value = (value << (bits - (shift % bits)) |
        (value >> (shift % bits)))));
}

template <typename Value, if_integer<Value>>
constexpr Value rotate_right(const Value& value, size_t shift)
{
    // C++14: local variables allowed in constexpr.
    constexpr auto bits = width<Value>();
    return (value << (bits - (shift % bits))) | (value >> (shift % bits));
}

template <typename Value, if_integer<Value>>
constexpr Value rotate_left(Value& value, size_t shift)
{
    // C++14: local variables allowed in constexpr.
    constexpr auto bits = width<Value>();
    return ((value = (value << (shift % bits)) |
        (value >> (bits - (shift % bits)))));
}

template <typename Value, if_integer<Value>>
constexpr Value rotate_left(const Value& value, size_t shift)
{
    // C++14: local variables allowed in constexpr.
    constexpr auto bits = width<Value>();
    return (value << (shift % bits)) | (value >> (bits - (shift % bits)));
}

} // namespace system
} // namespace libbitcoin

#endif