void try_outgoing_connections ( void ) {
 static config_t * cfg = NULL ;
 char * name ;
 outgoing_t * outgoing ;
 outgoing_list = list_alloc ( ( list_action_t ) free_outgoing ) ;
 for ( cfg = lookup_config ( config_tree , "ConnectTo" ) ;
 cfg ;
 cfg = lookup_config_next ( config_tree , cfg ) ) {
 get_config_string ( cfg , & name ) ;
 if ( ! check_id ( name ) ) {
 logger ( LOG_ERR , "Invalid name for outgoing connection in %s line %d" , cfg -> file , cfg -> line ) ;
 free ( name ) ;
 continue ;
 }
 outgoing = xmalloc_and_zero ( sizeof ( * outgoing ) ) ;
 outgoing -> name = name ;
 list_insert_tail ( outgoing_list , outgoing ) ;
 setup_outgoing_connection ( outgoing ) ;
 }
 }