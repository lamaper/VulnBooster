ulong acl_get ( const char * host , const char * ip , const char * user , const char * db , my_bool db_is_pattern ) {
 ulong host_access = ~ ( ulong ) 0 , db_access = 0 ;
 uint i ;
 size_t key_length , copy_length ;
 char key [ ACL_KEY_LENGTH ] , * tmp_db , * end ;
 acl_entry * entry ;
 DBUG_ENTER ( "acl_get" ) ;
 copy_length = ( size_t ) ( strlen ( ip ? ip : "" ) + strlen ( user ? user : "" ) + strlen ( db ? db : "" ) ) + 2 ;
 if ( copy_length >= ACL_KEY_LENGTH ) DBUG_RETURN ( 0 ) ;
 VOID ( pthread_mutex_lock ( & acl_cache -> lock ) ) ;
 end = strmov ( ( tmp_db = strmov ( strmov ( key , ip ? ip : "" ) + 1 , user ) + 1 ) , db ) ;
 if ( lower_case_table_names ) {
 my_casedn_str ( files_charset_info , tmp_db ) ;
 db = tmp_db ;
 }
 key_length = ( size_t ) ( end - key ) ;
 if ( ! db_is_pattern && ( entry = ( acl_entry * ) acl_cache -> search ( ( uchar * ) key , key_length ) ) ) {
 db_access = entry -> access ;
 VOID ( pthread_mutex_unlock ( & acl_cache -> lock ) ) ;
 DBUG_PRINT ( "exit" , ( "access: 0x%lx" , db_access ) ) ;
 DBUG_RETURN ( db_access ) ;
 }
 for ( i = 0 ;
 i < acl_dbs . elements ;
 i ++ ) {
 ACL_DB * acl_db = dynamic_element ( & acl_dbs , i , ACL_DB * ) ;
 if ( ! acl_db -> user || ! strcmp ( user , acl_db -> user ) ) {
 if ( compare_hostname ( & acl_db -> host , host , ip ) ) {
 if ( ! acl_db -> db || ! wild_compare ( db , acl_db -> db , db_is_pattern ) ) {
 db_access = acl_db -> access ;
 if ( acl_db -> host . hostname ) goto exit ;
 break ;
 }
 }
 }
 }
 if ( ! db_access ) goto exit ;
 host_access = 0 ;
 for ( i = 0 ;
 i < acl_hosts . elements ;
 i ++ ) {
 ACL_HOST * acl_host = dynamic_element ( & acl_hosts , i , ACL_HOST * ) ;
 if ( compare_hostname ( & acl_host -> host , host , ip ) ) {
 if ( ! acl_host -> db || ! wild_compare ( db , acl_host -> db , db_is_pattern ) ) {
 host_access = acl_host -> access ;
 break ;
 }
 }
 }
 exit : if ( ! db_is_pattern && ( entry = ( acl_entry * ) malloc ( sizeof ( acl_entry ) + key_length ) ) ) {
 entry -> access = ( db_access & host_access ) ;
 entry -> length = key_length ;
 memcpy ( ( uchar * ) entry -> key , key , key_length ) ;
 acl_cache -> add ( entry ) ;
 }
 VOID ( pthread_mutex_unlock ( & acl_cache -> lock ) ) ;
 DBUG_PRINT ( "exit" , ( "access: 0x%lx" , db_access & host_access ) ) ;
 DBUG_RETURN ( db_access & host_access ) ;
 }