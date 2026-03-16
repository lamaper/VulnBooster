bool check_grant_all_columns ( THD * thd , ulong want_access_arg , Field_iterator_table_ref * fields ) {
 Security_context * sctx = thd -> security_ctx ;
 ulong want_access = want_access_arg ;
 const char * table_name = NULL ;
 const char * db_name ;
 GRANT_INFO * grant ;
 GRANT_TABLE * grant_table = NULL ;
 bool using_column_privileges = FALSE ;
 rw_rdlock ( & LOCK_grant ) ;
 for ( ;
 ! fields -> end_of_fields ( ) ;
 fields -> next ( ) ) {
 const char * field_name = fields -> name ( ) ;
 if ( table_name != fields -> get_table_name ( ) ) {
 table_name = fields -> get_table_name ( ) ;
 db_name = fields -> get_db_name ( ) ;
 grant = fields -> grant ( ) ;
 want_access = want_access_arg & ~ grant -> privilege ;
 if ( want_access ) {
 if ( grant -> version != grant_version ) {
 grant -> grant_table = table_hash_search ( sctx -> host , sctx -> ip , db_name , sctx -> priv_user , table_name , 0 ) ;
 grant -> version = grant_version ;
 }
 grant_table = grant -> grant_table ;
 DBUG_ASSERT ( grant_table ) ;
 }
 }
 if ( want_access ) {
 GRANT_COLUMN * grant_column = column_hash_search ( grant_table , field_name , ( uint ) strlen ( field_name ) ) ;
 if ( grant_column ) using_column_privileges = TRUE ;
 if ( ! grant_column || ( ~ grant_column -> rights & want_access ) ) goto err ;
 }
 }
 rw_unlock ( & LOCK_grant ) ;
 return 0 ;
 err : rw_unlock ( & LOCK_grant ) ;
 char command [ 128 ] ;
 get_privilege_desc ( command , sizeof ( command ) , want_access ) ;
 if ( using_column_privileges ) my_error ( ER_TABLEACCESS_DENIED_ERROR , MYF ( 0 ) , command , sctx -> priv_user , sctx -> host_or_ip , table_name ) ;
 else my_error ( ER_COLUMNACCESS_DENIED_ERROR , MYF ( 0 ) , command , sctx -> priv_user , sctx -> host_or_ip , fields -> name ( ) , table_name ) ;
 return 1 ;
 }