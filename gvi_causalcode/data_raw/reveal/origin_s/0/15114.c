static my_bool grant_load_procs_priv ( TABLE * p_table ) {
 MEM_ROOT * memex_ptr ;
 my_bool return_val = 1 ;
 bool check_no_resolve = specialflag & SPECIAL_NO_RESOLVE ;
 MEM_ROOT * * save_mem_root_ptr = my_pthread_getspecific_ptr ( MEM_ROOT * * , THR_MALLOC ) ;
 DBUG_ENTER ( "grant_load_procs_priv" ) ;
 ( void ) hash_init ( & proc_priv_hash , & my_charset_utf8_bin , 0 , 0 , 0 , ( hash_get_key ) get_grant_table , 0 , 0 ) ;
 ( void ) hash_init ( & func_priv_hash , & my_charset_utf8_bin , 0 , 0 , 0 , ( hash_get_key ) get_grant_table , 0 , 0 ) ;
 p_table -> file -> ha_index_init ( 0 , 1 ) ;
 p_table -> use_all_columns ( ) ;
 if ( ! p_table -> file -> index_first ( p_table -> record [ 0 ] ) ) {
 memex_ptr = & memex ;
 my_pthread_setspecific_ptr ( THR_MALLOC , & memex_ptr ) ;
 do {
 GRANT_NAME * mem_check ;
 HASH * hash ;
 if ( ! ( mem_check = new ( memex_ptr ) GRANT_NAME ( p_table , TRUE ) ) ) {
 goto end_unlock ;
 }
 if ( check_no_resolve ) {
 if ( hostname_requires_resolving ( mem_check -> host . hostname ) ) {
 sql_print_warning ( "'procs_priv' entry '%s %s@%s' " "ignored in --skip-name-resolve mode." , mem_check -> tname , mem_check -> user , mem_check -> host . hostname ? mem_check -> host . hostname : "" ) ;
 continue ;
 }
 }
 if ( p_table -> field [ 4 ] -> val_int ( ) == TYPE_ENUM_PROCEDURE ) {
 hash = & proc_priv_hash ;
 }
 else if ( p_table -> field [ 4 ] -> val_int ( ) == TYPE_ENUM_FUNCTION ) {
 hash = & func_priv_hash ;
 }
 else {
 sql_print_warning ( "'procs_priv' entry '%s' " "ignored, bad routine type" , mem_check -> tname ) ;
 continue ;
 }
 mem_check -> privs = fix_rights_for_procedure ( mem_check -> privs ) ;
 if ( ! mem_check -> ok ( ) ) delete mem_check ;
 else if ( my_hash_insert ( hash , ( uchar * ) mem_check ) ) {
 delete mem_check ;
 goto end_unlock ;
 }
 }
 while ( ! p_table -> file -> index_next ( p_table -> record [ 0 ] ) ) ;
 }
 return_val = 0 ;
 end_unlock : p_table -> file -> ha_index_end ( ) ;
 my_pthread_setspecific_ptr ( THR_MALLOC , save_mem_root_ptr ) ;
 DBUG_RETURN ( return_val ) ;
 }