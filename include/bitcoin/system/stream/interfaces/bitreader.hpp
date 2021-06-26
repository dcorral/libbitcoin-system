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

// Sponsored in part by Digital Contract Design, LLC

#ifndef LIBBITCOIN_SYSTEM_STREAM_INTERFACES_BITREADER_HPP
#define LIBBITCOIN_SYSTEM_STREAM_INTERFACES_BITREADER_HPP

#include <cstddef>
#include <cstdint>
#include <bitcoin/system/constants.hpp>
#include <bitcoin/system/stream/interfaces/bytereader.hpp>
#include <bitcoin/system/type_constraints.hpp>

namespace libbitcoin {
namespace system {

/// A bit reader interface.
class bitreader
  : public virtual bytereader
{
public:
    /// Read one bit (high to low).
    virtual bool read_bit() noexcept = 0;

    /// Read size bits into an integer (high to low).
    template <typename Integer, if_integer<Integer> = true>
    Integer read_bits(size_t bits) noexcept /* = 0 */;

    // vc++ emits 'constant' error with '= 0' above.

    /// Advance the iterator.
    virtual void skip_bit(size_t bits=one) noexcept = 0;
};

} // namespace system
} // namespace libbitcoin

#endif