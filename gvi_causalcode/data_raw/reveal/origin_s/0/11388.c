int lcc_network_buffer_finalize ( lcc_network_buffer_t * nb ) {
 if ( nb == NULL ) return ( EINVAL ) ;

 else if ( nb -> seclevel == ENCRYPT ) nb_add_encryption ( nb ) ;

 }