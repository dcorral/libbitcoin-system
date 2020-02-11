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
#ifndef LIBBITCOIN_CONTAINER_SOURCE_HPP
#define LIBBITCOIN_CONTAINER_SOURCE_HPP

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <boost/iostreams/stream.hpp>
#include <bitcoin/bitcoin/define.hpp>
//#include <bitcoin/bitcoin/math/limits.hpp>
//#include <bitcoin/bitcoin/utility/data.hpp>
#include <bitcoin/bitcoin/utility/container_source.hpp>
#include <bitcoin/utility_data_chunk.hpp>

namespace libbitcoin {
namespace api {

// modified from boost.iostreams example
// boost.org/doc/libs/1_55_0/libs/iostreams/doc/tutorial/container_source.html
template <typename Container, typename SourceType, typename CharType>
class BC_API utility_container_source
{
public:
    typedef CharType char_type;
    typedef boost::iostreams::source_tag category;

    utility_container_source(const Container& container)
      : value(new libbitcoin::container_source(container))
    {
        static_assert(sizeof(SourceType) == sizeof(CharType), "invalid size");
    }

    std::streamsize read(char_type* buffer, std::streamsize size)
    {
        return value.read(buffer, size);
    }

    libbitcoin::container_source getValue() {
        return value;
    }

    void setValue(libbitcoin::container_source value) {
        this->value = value;
    }
private:
    libbitcoin::container_source value;

//private:
//    const Container& container_;
//    typename Container::size_type position_;
};

template <typename Container>
using utility_byte_source = utility_container_source<Container, uint8_t, char>;

template <typename Container>
using utility_stream_source = boost::iostreams::stream<byte_source<Container>>;

using utility_data_source = utility_stream_source<libbitcoin::api::utility_data_chunk>;

} // namespace api
} // namespace libbitcoin

#endif
