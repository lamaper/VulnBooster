void check_new_cluster ( void ) {
 get_db_and_rel_infos ( & new_cluster ) ;
 check_new_cluster_is_empty ( ) ;
 check_databases_are_compatible ( ) ;
 check_loadable_libraries ( ) ;
 if ( user_opts . transfer_mode == TRANSFER_MODE_LINK ) check_hard_link ( ) ;
 check_is_install_user ( & new_cluster ) ;
 check_for_prepared_transactions ( & new_cluster ) ;
 }