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
#include <bitcoin/explorer/commands/ec-to-public.hpp>

#include <iostream>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/define.hpp>


namespace libbitcoin {
namespace explorer {
namespace commands {
using namespace bc::wallet;

console_result ec_priavte_to_address(bc::explorer::config::ec_private& secret, 
        payment_address& address, uint8_t address_version = 0x32)
{
    ec_compressed point;
    secret_to_public(point, secret);

    explorer::config::byte version(address_version);

    // Serialize to the original compression state.
    ec_public ec_public_key(point, true);
    address = payment_address(ec_public_key, version);

    return console_result::okay;
}

console_result ec_priavte_to_public(bc::explorer::config::ec_private& secret, 
        ec_public& ec_public_key, uint8_t address_version = 0x32)
{
    ec_compressed point;
    secret_to_public(point, secret);

    explorer::config::byte version(address_version);

    // Serialize to the original compression state.
    ec_public_key = ec_public(point, true);
    return console_result::okay;
}


// In the case of failure this produces ec_compressed_null.
console_result ec_to_public::invoke(std::ostream& output, std::ostream& error)
{
    const auto& secret = get_ec_private_key_argument();
    const auto& uncompressed = get_uncompressed_option();

    ec_compressed point;
    secret_to_public(point, secret);

    // Serialize to the original compression state.
    output << ec_public(point, !uncompressed) << std::flush;
    return console_result::okay;
}

} //namespace commands 
} //namespace explorer 
} //namespace libbitcoin 
