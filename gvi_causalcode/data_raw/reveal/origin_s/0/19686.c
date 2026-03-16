static uint32_t _get_wckeyid ( mysql_conn_t * mysql_conn , char * * name , uid_t uid , char * cluster , uint32_t associd ) {
 uint32_t wckeyid = 0 ;
 if ( slurm_get_track_wckey ( ) ) {
 slurmdb_wckey_rec_t wckey_rec ;
 char * user = NULL ;
 if ( ! ( user = _get_user_from_associd ( mysql_conn , cluster , associd ) ) ) {
 error ( "No user for associd %u" , associd ) ;
 goto no_wckeyid ;
 }
 if ( ! * name ) {
 slurmdb_user_rec_t user_rec ;
 memset ( & user_rec , 0 , sizeof ( slurmdb_user_rec_t ) ) ;
 user_rec . uid = NO_VAL ;
 user_rec . name = user ;
 if ( assoc_mgr_fill_in_user ( mysql_conn , & user_rec , 1 , NULL ) != SLURM_SUCCESS ) {
 error ( "No user by name of %s assoc %u" , user , associd ) ;
 xfree ( user ) ;
 goto no_wckeyid ;
 }
 if ( user_rec . default_wckey ) * name = xstrdup_printf ( "*%s" , user_rec . default_wckey ) ;
 else * name = xstrdup_printf ( "*" ) ;
 }
 memset ( & wckey_rec , 0 , sizeof ( slurmdb_wckey_rec_t ) ) ;
 wckey_rec . name = ( * name ) ;
 wckey_rec . uid = NO_VAL ;
 wckey_rec . user = user ;
 wckey_rec . cluster = cluster ;
 if ( assoc_mgr_fill_in_wckey ( mysql_conn , & wckey_rec , ACCOUNTING_ENFORCE_WCKEYS , NULL ) != SLURM_SUCCESS ) {
 List wckey_list = NULL ;
 slurmdb_wckey_rec_t * wckey_ptr = NULL ;
 wckey_list = list_create ( slurmdb_destroy_wckey_rec ) ;
 wckey_ptr = xmalloc ( sizeof ( slurmdb_wckey_rec_t ) ) ;
 wckey_ptr -> name = xstrdup ( ( * name ) ) ;
 wckey_ptr -> user = xstrdup ( user ) ;
 wckey_ptr -> cluster = xstrdup ( cluster ) ;
 list_append ( wckey_list , wckey_ptr ) ;
 if ( * name [ 0 ] == '*' ) {
 wckey_rec . name = ( * name ) + 1 ;
 if ( assoc_mgr_fill_in_wckey ( mysql_conn , & wckey_rec , ACCOUNTING_ENFORCE_WCKEYS , NULL ) != SLURM_SUCCESS ) {
 wckey_ptr = xmalloc ( sizeof ( slurmdb_wckey_rec_t ) ) ;
 wckey_ptr -> name = xstrdup ( wckey_rec . name ) ;
 wckey_ptr -> user = xstrdup ( user ) ;
 wckey_ptr -> cluster = xstrdup ( cluster ) ;
 list_prepend ( wckey_list , wckey_ptr ) ;
 }
 wckey_rec . name = ( * name ) ;
 }
 if ( as_mysql_add_wckeys ( mysql_conn , slurm_get_slurm_user_id ( ) , wckey_list ) == SLURM_SUCCESS ) acct_storage_p_commit ( mysql_conn , 1 ) ;
 assoc_mgr_fill_in_wckey ( mysql_conn , & wckey_rec , ACCOUNTING_ENFORCE_WCKEYS , NULL ) ;
 FREE_NULL_LIST ( wckey_list ) ;
 }
 xfree ( user ) ;
 wckeyid = wckey_rec . id ;
 }
 no_wckeyid : return wckeyid ;
 }