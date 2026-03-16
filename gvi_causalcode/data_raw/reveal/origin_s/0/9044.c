static my_bool grant_load ( THD * thd , TABLE_LIST * tables ) {
 MEM_ROOT * memex_ptr ;
 my_bool return_val = 1 ;
 TABLE * t_table = 0 , * c_table = 0 ;
 bool check_no_resolve = specialflag & SPECIAL_NO_RESOLVE ;
 MEM_ROOT * * save_mem_root_ptr = my_pthread_getspecific_ptr ( MEM_ROOT * * , THR_MALLOC ) ;
 ulong old_sql_mode = thd -> variables . sql_mode ;
 DBUG_ENTER ( "grant_load" ) ;
 thd -> variables . sql_mode &= ~ MODE_PAD_CHAR_TO_FULL_LENGTH ;
 ( void ) hash_init ( & column_priv_hash , & my_charset_utf8_bin , 0 , 0 , 0 , ( hash_get_key ) get_grant_table , ( hash_free_key ) free_grant_table , 0 ) ;
 t_table = tables [ 0 ] . table ;
 c_table = tables [ 1 ] . table ;
 t_table -> file -> ha_index_init ( 0 , 1 ) ;
 t_table -> use_all_columns ( ) ;
 c_table -> use_all_columns ( ) ;
 if ( ! t_table -> file -> index_first ( t_table -> record [ 0 ] ) ) {
 memex_ptr = & memex ;
 my_pthread_setspecific_ptr ( THR_MALLOC , & memex_ptr ) ;
 do {
 GRANT_TABLE * mem_check ;
 if ( ! ( mem_check = new ( memex_ptr ) GRANT_TABLE ( t_table , c_table ) ) ) {
 goto end_unlock ;
 }
 if ( check_no_resolve ) {
 if ( hostname_requires_resolving ( mem_check -> host . hostname ) ) {
 sql_print_warning ( "'tables_priv' entry '%s %s@%s' " "ignored in --skip-name-resolve mode." , mem_check -> tname , mem_check -> user ? mem_check -> user : "" , mem_check -> host . hostname ? mem_check -> host . hostname : "" ) ;
 continue ;
 }
 }
 if ( ! mem_check -> ok ( ) ) delete mem_check ;
 else if ( my_hash_insert ( & column_priv_hash , ( uchar * ) mem_check ) ) {
 delete mem_check ;
 goto end_unlock ;
 }
 }
 while ( ! t_table -> file -> index_next ( t_table -> record [ 0 ] ) ) ;
 }
 return_val = 0 ;
 end_unlock : thd -> variables . sql_mode = old_sql_mode ;
 t_table -> file -> ha_index_end ( ) ;
 my_pthread_setspecific_ptr ( THR_MALLOC , save_mem_root_ptr ) ;
 DBUG_RETURN ( return_val ) ;
 }