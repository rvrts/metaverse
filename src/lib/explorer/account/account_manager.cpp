/**
 * Copyright (c) 2016 mvs developers 
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

#include <bitcoin/explorer/account/account_manager.hpp>
#include <vector>

namespace libbitcoin {
namespace explorer {
namespace account {

account_manager::paccount account_manager::get_account(account_auth&& auth, const std::string& last_word)
{
    auto acc = chain_.is_account_passwd_valid(auth.name, auth.auth);
    auto&& mnemonic = acc->get_mnemonic();
    std::vector<std::string> results;
    boost::split(results, mnemonic, boost::is_any_of(" "));

    if (*results.rbegin() != last_word){
        throw std::logic_error{"last word not matching."};
    }

	return acc;
}

account_manager::paccount account_manager::is_account_passwd_valid(account_auth&& auth)
{
    return chain_.is_account_passwd_valid(auth.name, auth.auth);
}

}// acccount
}// explorer
}// libbitcoin
