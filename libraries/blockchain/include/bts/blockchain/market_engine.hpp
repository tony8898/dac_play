#include <bts/blockchain/chain_database_impl.hpp>
#include <bts/blockchain/transaction_evaluation_state.hpp>

namespace bts { namespace blockchain { namespace detail {

  class market_engine
  {
  public:
    market_engine( const pending_chain_state_ptr ps, const chain_database_impl& cdi );
    /** return true if execute was successful and applied */
    bool execute( asset_id_type quote_id, asset_id_type base_id, const fc::time_point_sec timestamp );

    static asset get_interest_paid(const asset& total_amount_paid, const price& apr, uint32_t age_seconds);
    static asset get_interest_owed(const asset& principle, const price& apr, uint32_t age_seconds);

  private:
    void push_market_transaction( const market_transaction& mtrx );

    void pay_current_bid( market_transaction& mtrx,
                          asset_record& base,
                          asset_record& quote_asset );

    void pay_current_ask( market_transaction& mtrx,
                          asset_record& base,
                          asset_record& quote_asset );

    bool get_next_bid();
    bool get_next_ask();
    bool get_next_ask_order();

    void handle_liquidation( const price& liqudation_price );

    /**
      *  This method should not affect market execution or validation and
      *  is for historical purposes only.
      */
    void update_market_history( const asset& trading_volume,
                                const price& highest_price,
                                const price& lowest_price,
                                const price& opening_price,
                                const price& closing_price,
                                const fc::time_point_sec timestamp );

    transaction_evaluation_state  _eval_state;

    pending_chain_state_ptr       _pending_state;
    pending_chain_state_ptr       _prior_state;
    const chain_database_impl&    _db_impl;

    optional<market_order>        _current_bid;
    optional<market_order>        _current_ask;

    asset_id_type                 _quote_id;
    asset_id_type                 _base_id;
    oprice                        _feed_price;

    int                           _orders_filled = 0;
    int                           _current_pass;

  public:
    vector<market_transaction>    _market_transactions;

  private:
    bts::db::cached_level_map< market_index_key, order_record >::iterator         _bid_itr;
    bts::db::cached_level_map< market_index_key, order_record >::iterator         _ask_itr;
  };

} } } // end namespace bts::blockchain::detail
