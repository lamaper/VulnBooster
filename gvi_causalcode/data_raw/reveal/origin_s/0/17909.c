bool acl_getroot_no_password ( Security_context * sctx , char * user , char * host , char * ip , char * db ) {
 int res = 1 ;
 uint i ;
 ACL_USER * acl_user = 0 ;
 DBUG_ENTER ( "acl_getroot_no_password" ) ;
 DBUG_PRINT ( "enter" , ( "Host: '%s', Ip: '%s', User: '%s', db: '%s'" , ( host ? host : "(NULL)" ) , ( ip ? ip : "(NULL)" ) , user , ( db ? db : "(NULL)" ) ) ) ;
 sctx -> user = user ;
 sctx -> host = host ;
 sctx -> ip = ip ;
 sctx -> host_or_ip = host ? host : ( ip ? ip : "" ) ;
 if ( ! initialized ) {
 sctx -> skip_grants ( ) ;
 DBUG_RETURN ( FALSE ) ;
 }
 VOID ( pthread_mutex_lock ( & acl_cache -> lock ) ) ;
 sctx -> master_access = 0 ;
 sctx -> db_access = 0 ;
 sctx -> priv_user = ( char * ) "" ;
 * sctx -> priv_host = 0 ;
 for ( i = 0 ;
 i < acl_users . elements ;
 i ++ ) {
 ACL_USER * acl_user_tmp = dynamic_element ( & acl_users , i , ACL_USER * ) ;
 if ( ( ! acl_user_tmp -> user && ! user [ 0 ] ) || ( acl_user_tmp -> user && strcmp ( user , acl_user_tmp -> user ) == 0 ) ) {
 if ( compare_hostname ( & acl_user_tmp -> host , host , ip ) ) {
 acl_user = acl_user_tmp ;
 res = 0 ;
 break ;
 }
 }
 }
 if ( acl_user ) {
 for ( i = 0 ;
 i < acl_dbs . elements ;
 i ++ ) {
 ACL_DB * acl_db = dynamic_element ( & acl_dbs , i , ACL_DB * ) ;
 if ( ! acl_db -> user || ( user && user [ 0 ] && ! strcmp ( user , acl_db -> user ) ) ) {
 if ( compare_hostname ( & acl_db -> host , host , ip ) ) {
 if ( ! acl_db -> db || ( db && ! wild_compare ( db , acl_db -> db , 0 ) ) ) {
 sctx -> db_access = acl_db -> access ;
 break ;
 }
 }
 }
 }
 sctx -> master_access = acl_user -> access ;
 sctx -> priv_user = acl_user -> user ? user : ( char * ) "" ;
 if ( acl_user -> host . hostname ) strmake ( sctx -> priv_host , acl_user -> host . hostname , MAX_HOSTNAME - 1 ) ;
 else * sctx -> priv_host = 0 ;
 }
 VOID ( pthread_mutex_unlock ( & acl_cache -> lock ) ) ;
 DBUG_RETURN ( res ) ;
 }