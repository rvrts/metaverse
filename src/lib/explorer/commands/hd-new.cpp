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
#include <bitcoin/explorer/commands/hd-new.hpp>

#include <iostream>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/define.hpp>



// The BX_HD_NEW_INVALID_KEY condition is uncovered by test.
// This is because is not known what seed will produce an invalid key.
namespace libbitcoin {
namespace explorer {
namespace commands {

console_result hd_new_impl(std::ostream& error, 
        const data_chunk& seed,
        std::shared_ptr<bc::wallet::hd_private> private_key, 
        uint32_t version = 76066276)
{
    if (seed.size() < minimum_seed_size)
    {
        error << BX_HD_NEW_SHORT_SEED << std::flush;
        return console_result::failure;
    }

    // We require the private version, but public is unused here.
    const auto prefixes = bc::wallet::hd_private::to_prefixes(version, 0);
    private_key = std::make_shared<bc::wallet::hd_private>(seed, prefixes);

    return console_result::okay;
}

console_result hd_new::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto version = get_version_option();
    const data_chunk& seed = get_seed_argument();

    std::shared_ptr<bc::wallet::hd_private> private_key{nullptr};
    if (hd_new_impl(error, seed, private_key, version))
        return console_result::failure;

    if (!(*private_key))
    {
        error << BX_HD_NEW_INVALID_KEY << std::flush;
        return console_result::failure;
    }

    output << *private_key << std::flush;
    return console_result::okay;
}

} //namespace commands 
} //namespace explorer 
} //namespace libbitcoin 
