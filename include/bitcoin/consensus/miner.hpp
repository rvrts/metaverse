
#ifndef MVS_CONSENSUS_MINER_HPP
#define MVS_CONSENSUS_MINER_HPP

#include <vector>
#include <boost/thread.hpp>

#include "bitcoin/blockchain/block_chain_impl.hpp"
#include "bitcoin/blockchain/transaction_pool.hpp"
#include "bitcoin/bitcoin/chain/block.hpp"
#include "bitcoin/bitcoin/chain/input.hpp"
#include <bitcoin/bitcoin/wallet/ec_public.hpp>
#include <bitcoin/blockchain/settings.hpp>

namespace libbitcoin{
namespace node{
	class p2p_node;
}
}

namespace libbitcoin{
namespace consensus{

BC_CONSTEXPR unsigned int min_tx_fee_per_kb = 1000;
BC_CONSTEXPR unsigned int median_time_span = 11;
BC_CONSTEXPR uint32_t version = 1;

extern int bucket_size;
extern vector<uint64_t> lock_heights;

class miner
{
public:
	typedef message::block_message block;
	typedef std::shared_ptr<message::block_message> block_ptr;
	typedef chain::header header;
	typedef chain::transaction transaction;
	typedef message::transaction_message::ptr transaction_ptr;
	typedef blockchain::block_chain_impl block_chain_impl;
	typedef blockchain::transaction_pool transaction_pool;
	typedef libbitcoin::node::p2p_node p2p_node;

	miner(p2p_node& node);
	~miner();

	enum state
	{
		init_,
		exit_
	};

	bool start(const wallet::payment_address& pay_address);
	bool start(const std::string& pay_public_key);
	bool stop();
	static block_ptr create_genesis_block(bool is_mainnet);
	bool script_hash_signature_operations_count(size_t &count, chain::input::list& inputs, vector<transaction_ptr>& transactions);
	bool script_hash_signature_operations_count(size_t &count, chain::input& input, vector<transaction_ptr>& transactions);
	transaction_ptr create_coinbase_tx(const wallet::payment_address& pay_addres, uint64_t value, uint64_t block_height, int lock_height);

	block_ptr get_block();
	bool get_work(std::string& seed_hash, std::string& header_hash, std::string& boundary);
	bool put_result(const std::string& nounce, const std::string& mix_hash, const std::string& header_hash);
	bool set_miner_public_key(const string& public_key);
	bool set_miner_payment_address(const wallet::payment_address& address);
	void get_state(uint64_t &height,  uint64_t &rate, string& difficulty, bool& is_mining);
	bool get_block_header(chain::header& block_header, const string& para);

	static int get_lock_heights_index(uint64_t height);
	static uint64_t calculate_block_subsidy(uint64_t height, bool is_testnet);
	static uint64_t calculate_lockblock_reward(uint64_t lcok_heights, uint64_t num);

private:
	void work(const wallet::payment_address pay_address);
	block_ptr create_new_block(const wallet::payment_address& pay_addres);
	unsigned int get_adjust_time(uint64_t height);
	unsigned int get_median_time_past(uint64_t height);
	bool get_transaction(std::vector<transaction_ptr>&);
	bool is_exit();
	uint64_t store_block(block_ptr block);
	uint64_t get_height();
	bool is_stop_miner(uint64_t block_height);

private:
	p2p_node& node_;
	std::shared_ptr<boost::thread> thread_;
	mutable state state_;

	block_ptr new_block_;
	wallet::payment_address pay_address_;
	const blockchain::settings& setting_;
};

}
}

#endif
