static void acl_update_db ( const char * user , const char * host , const char * db , ulong privileges ) {
 safe_mutex_assert_owner ( & acl_cache -> lock ) ;
 for ( uint i = 0 ;
 i < acl_dbs . elements ;
 i ++ ) {
 ACL_DB * acl_db = dynamic_element ( & acl_dbs , i , ACL_DB * ) ;
 if ( ( ! acl_db -> user && ! user [ 0 ] ) || ( acl_db -> user && ! strcmp ( user , acl_db -> user ) ) ) {
 if ( ( ! acl_db -> host . hostname && ! host [ 0 ] ) || ( acl_db -> host . hostname && ! strcmp ( host , acl_db -> host . hostname ) ) ) {
 if ( ( ! acl_db -> db && ! db [ 0 ] ) || ( acl_db -> db && ! strcmp ( db , acl_db -> db ) ) ) {
 if ( privileges ) acl_db -> access = privileges ;
 else delete_dynamic_element ( & acl_dbs , i ) ;
 }
 }
 }
 }
 }