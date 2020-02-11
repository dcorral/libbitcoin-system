/**
 * Copyright (c) 2011-2017 libbitcoin developers (see AUTHORS)
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
#ifndef LIBBITCOIN__CHAIN_COMPACT_HPP
#define LIBBITCOIN__CHAIN_COMPACT_HPP

#include <cstdint>
#include <bitcoin/bitcoin/define.hpp>
//#include <bitcoin/bitcoin/math/hash.hpp>
#include <bitcoin/bitcoin/chain/compact.hpp>
#include <bitcoin/math_uint256_t.hpp>

namespace libbitcoin {
//namespace chain {
namespace api {

/// A signed but zero-floored scientific notation in 32 bits.
class BC_API chain_compact
{
public:
    /// Construct a normal form compact number from a 32 bit compact number.
//    explicit compact(uint32_t compact);

    /// Construct a normal form compact number from a 256 bit number
    explicit chain_compact(const math_uint256_t& big);

    /// True if construction overflowed.
    bool is_overflowed() const;

    /// Consensus-normalized compact number value.
    /// This is derived from the construction parameter.
    uint32_t normal() const;

    /// Big number that the compact number represents.
    /// This is either saved or generated from the construction parameter.
//    operator const uint256_t&() const;
    const math_uint256_t& to_uint256_t() const;

    chain::compact getValue() {
        return value;
    }

    void setValue(chain::compact value) {
        this->value = value;
    }
private:
    chain::compact value;
//    static bool from_compact(uint256_t& out, uint32_t compact);
//    static uint32_t from_big(const uint256_t& big);
//
//    uint256_t big_;
//    uint32_t normal_;
//    bool overflowed_;
};

} // namespace api
//} // namespace chain
} // namespace libbitcoin

#endif