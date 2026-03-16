void evdns_set_transaction_id_fn ( ev_uint16_t ( * fn ) ( void ) ) {
 if ( fn ) trans_id_function = fn ;
 else trans_id_function = default_transaction_id_fn ;
 }