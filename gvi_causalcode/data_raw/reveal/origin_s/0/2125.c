static void acl_insert_db ( const char * user , const char * host , const char * db , ulong privileges ) {
 ACL_DB acl_db ;
 safe_mutex_assert_owner ( & acl_cache -> lock ) ;
 acl_db . user = strdup_root ( & mem , user ) ;
 update_hostname ( & acl_db . host , * host ? strdup_root ( & mem , host ) : 0 ) ;
 acl_db . db = strdup_root ( & mem , db ) ;
 acl_db . access = privileges ;
 acl_db . sort = get_sort ( 3 , acl_db . host . hostname , acl_db . db , acl_db . user ) ;
 VOID ( push_dynamic ( & acl_dbs , ( uchar * ) & acl_db ) ) ;
 my_qsort ( ( uchar * ) dynamic_element ( & acl_dbs , 0 , ACL_DB * ) , acl_dbs . elements , sizeof ( ACL_DB ) , ( qsort_cmp ) acl_compare ) ;
 }