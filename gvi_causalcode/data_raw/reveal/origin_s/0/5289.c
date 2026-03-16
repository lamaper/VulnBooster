void check_and_dump_old_cluster ( bool live_check ) {
 if ( ! live_check ) start_postmaster ( & old_cluster , true ) ;
 get_db_and_rel_infos ( & old_cluster ) ;
 init_tablespaces ( ) ;
 get_loadable_libraries ( ) ;
 check_is_install_user ( & old_cluster ) ;
 check_proper_datallowconn ( & old_cluster ) ;
 check_for_prepared_transactions ( & old_cluster ) ;
 check_for_reg_data_type_usage ( & old_cluster ) ;
 check_for_isn_and_int8_passing_mismatch ( & old_cluster ) ;
 if ( GET_MAJOR_VERSION ( old_cluster . major_version ) <= 905 ) check_for_pg_role_prefix ( & old_cluster ) ;
 if ( GET_MAJOR_VERSION ( old_cluster . major_version ) == 904 && old_cluster . controldata . cat_ver < JSONB_FORMAT_CHANGE_CAT_VER ) check_for_jsonb_9_4_usage ( & old_cluster ) ;
 if ( GET_MAJOR_VERSION ( old_cluster . major_version ) <= 903 ) old_9_3_check_for_line_data_type_usage ( & old_cluster ) ;
 if ( GET_MAJOR_VERSION ( old_cluster . major_version ) <= 804 ) new_9_0_populate_pg_largeobject_metadata ( & old_cluster , true ) ;
 if ( ! user_opts . check ) generate_old_dump ( ) ;
 if ( ! live_check ) stop_postmaster ( false ) ;
 }