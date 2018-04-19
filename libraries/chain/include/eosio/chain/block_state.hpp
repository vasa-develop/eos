#pragma once
#include <eosio/chain/block_header_state.hpp>
#include <eosio/chain/block.hpp>
#include <eosio/chain/transaction_metadata.hpp>

namespace eosio { namespace chain {

   /**
    *  For each action dispatched this receipt is generated
    */
   struct action_receipt {
      account_name                    receiver;
      digest_type                     act_digest;
      uint64_t                        global_sequence = 0; ///< total number of actions dispatched since genesis
      uint64_t                        recv_sequence = 0; ///< total number of actions with this receiver since genesis
      flat_map<account_name,uint32_t> auth_sequence; 

      digest_type digest()const { return digest_type::hash(*this); }
   };

   struct block_state : public block_header_state {
      block_state( const block_header_state& cur ):block_header_state(cur){}
      block_state( const block_header_state& prev, signed_block_ptr b );
      block_state( const block_header_state& prev, block_timestamp_type when );
      block_state() = default;

      /// weak_ptr prev_block_state....
      signed_block_ptr                                    block;
      bool                                                validated = false;
   };

   typedef std::shared_ptr<block_state> block_state_ptr;



} } /// namespace eosio::chain

FC_REFLECT( eosio::chain::action_receipt, (receiver)(act_digest)(global_sequence)(recv_sequence)(auth_sequence) )
FC_REFLECT_DERIVED( eosio::chain::block_state, (eosio::chain::block_header_state), (block)(validated) )