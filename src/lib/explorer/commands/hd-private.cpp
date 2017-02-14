/**
 * Copyright (c) 2011-2015 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin-explorer.
 *
 * libbitcoin-explorer is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License with
 * additional permissions to the one published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version. For more information see LICENSE.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include <bitcoin/explorer/commands/hd-private.hpp>

#include <iostream>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/define.hpp>



namespace libbitcoin {
namespace explorer {
namespace commands {

console_result hd_private_impl(std::ostream& error,
        const uint32_t index,
        const bc::wallet::hd_private& private_key,
        bc::wallet::hd_private& child_private_key)

{
    bool hard = false;
    static constexpr auto first = bc::wallet::hd_first_hardened_key;
    const auto position = hard ? first + index : index;
    child_private_key = private_key.derive_private(position);

    if (!child_private_key)
    {
        error << "ERROR" << std::flush;
        return console_result::failure;
    }

    return console_result::okay;
}

console_result hd_private::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto hard = get_hard_option();
    const auto index = get_index_option();
    const auto& private_key = get_hd_private_key_argument();
    
    static constexpr auto first = bc::wallet::hd_first_hardened_key;
    const auto position = hard ? first + index : index;
    const auto child_private_key = private_key.derive_private(position);

    if (!child_private_key)
    {
        output << "ERROR" << std::flush;
        return console_result::failure;
    }
    
    output << child_private_key << std::flush;
    return console_result::okay;
}

} //namespace commands 
} //namespace explorer 
} //namespace libbitcoin 
