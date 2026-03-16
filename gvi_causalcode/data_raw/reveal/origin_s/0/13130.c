TSReturnCode TSHttpTxnInfoIntGet ( TSHttpTxn txnp , TSHttpTxnInfoKey key , TSMgmtInt * value ) {
 sdk_assert ( sdk_sanity_check_txn ( txnp ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_null_ptr ( ( void * ) value ) == TS_SUCCESS ) ;
 HttpSM * s = reinterpret_cast < HttpSM * > ( txnp ) ;
 HttpCacheSM * c_sm = & ( s -> get_cache_sm ( ) ) ;
 switch ( key ) {
 case TS_TXN_INFO_CACHE_HIT_RAM : * value = ( static_cast < TSMgmtInt > ( c_sm -> is_ram_cache_hit ( ) ) ) ;
 break ;
 case TS_TXN_INFO_CACHE_COMPRESSED_IN_RAM : * value = ( static_cast < TSMgmtInt > ( c_sm -> is_compressed_in_ram ( ) ) ) ;
 break ;
 case TS_TXN_INFO_CACHE_HIT_RWW : * value = ( static_cast < TSMgmtInt > ( c_sm -> is_readwhilewrite_inprogress ( ) ) ) ;
 break ;
 case TS_TXN_INFO_CACHE_OPEN_READ_TRIES : * value = ( static_cast < TSMgmtInt > ( c_sm -> get_open_read_tries ( ) ) ) ;
 break ;
 case TS_TXN_INFO_CACHE_OPEN_WRITE_TRIES : * value = ( static_cast < TSMgmtInt > ( c_sm -> get_open_write_tries ( ) ) ) ;
 break ;
 case TS_TXN_INFO_CACHE_VOLUME : * value = ( static_cast < TSMgmtInt > ( c_sm -> get_volume_number ( ) ) ) ;
 break ;
 default : return TS_ERROR ;
 }
 return TS_SUCCESS ;
 }