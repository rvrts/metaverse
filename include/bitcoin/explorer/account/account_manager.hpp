/**
 * Copyright (c) 2011-2015 metaverse developers (see AUTHORS)
 *
 * This file is part of mvs-node.
 *
 * libbitcoin is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License with
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

#pragma once

#include <cstdint>
#include <functional>
#include <string>
#include <vector>

#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/command.hpp>
#include <bitcoin/explorer/dispatch.hpp>
#include <bitcoin/bitcoin/chain/attachment/account/account.hpp>
#include <bitcoin/bitcoin/chain/attachment/account/account_address.hpp>

namespace libbitcoin {
namespace explorer {
namespace account {

struct BC_API account_auth
{
    std::string name;
    std::string auth;
};

class BC_API account_manager
{
public:
    typedef bc::blockchain::block_chain_impl chain_impl;
    typedef bc::consensus::miner miner_impl;
    typedef std::shared_ptr<std::vector<bc::chain::account>> account_list;
    typedef std::shared_ptr<bc::chain::account> paccount;

public:
    // construct
    account_manager() = delete;
    account_manager(chain_impl& blockchain, miner_impl& miner):
        chain_(blockchain) {
            paccounts_ = chain_.get_accounts();
    }
    ~account_manager() = default;

public:
    // query
    paccount get_account(account_auth&& auth, const std::string& last_word);
    paccount is_account_passwd_valid(account_auth&& auth);
    bool is_admin_account(account_auth&& auth);
    bool is_account_locked(account_auth&& auth);
    bool is_account_normal(account_auth&& auth);
    paccount list_accounts(account_auth&& auth);
    void list_balances(account_auth&& auth);

public:
    // write
    paccount get_new_account(account_auth&& auth);
    paccount import_account(account_auth&& auth, uint32_t address_count, std::string& mnemonic_phrase);
    bool lock_wallet(account_auth&& auth);
    bool lock_account(account_auth&& auth);
    bool unlock_account(account_auth&& auth);

private:
    // write
    bool store_account(std::shared_ptr<bc::chain::account> acc);

private:
    chain_impl& chain_;
    account_list paccounts_;
};


} // namespace account 
} // namespace explorer
} // namespace libbitcoin
