extern List as_mysql_remove_clusters ( mysql_conn_t * mysql_conn , uint32_t uid , slurmdb_cluster_cond_t * cluster_cond ) {
 ListIterator itr = NULL ;
 List ret_list = NULL ;
 List tmp_list = NULL ;
 int rc = SLURM_SUCCESS ;
 char * object = NULL ;
 char * extra = NULL , * query = NULL , * cluster_name = NULL , * name_char = NULL , * assoc_char = NULL ;
 time_t now = time ( NULL ) ;
 char * user_name = NULL ;
 slurmdb_wckey_cond_t wckey_cond ;
 MYSQL_RES * result = NULL ;
 MYSQL_ROW row ;
 bool jobs_running = 0 , fed_update = false ;
 if ( ! cluster_cond ) {
 error ( "we need something to change" ) ;
 return NULL ;
 }
 if ( check_connection ( mysql_conn ) != SLURM_SUCCESS ) return NULL ;
 if ( ! is_user_min_admin_level ( mysql_conn , uid , SLURMDB_ADMIN_SUPER_USER ) ) {
 errno = ESLURM_ACCESS_DENIED ;
 return NULL ;
 }
 cluster_cond -> with_deleted = 0 ;
 _setup_cluster_cond_limits ( cluster_cond , & extra ) ;
 if ( ! extra ) {
 error ( "Nothing to remove" ) ;
 return NULL ;
 }
 query = xstrdup_printf ( "select name,federation from %s%s;
" , cluster_table , extra ) ;
 xfree ( extra ) ;
 if ( ! ( result = mysql_db_query_ret ( mysql_conn , query , 0 ) ) ) {
 xfree ( query ) ;
 return NULL ;
 }
 rc = 0 ;
 ret_list = list_create ( slurm_destroy_char ) ;
 if ( ! mysql_num_rows ( result ) ) {
 mysql_free_result ( result ) ;
 errno = SLURM_NO_CHANGE_IN_DATA ;
 if ( debug_flags & DEBUG_FLAG_DB_ASSOC ) DB_DEBUG ( mysql_conn -> conn , "didn't effect anything\n%s" , query ) ;
 xfree ( query ) ;
 return ret_list ;
 }
 xfree ( query ) ;
 assoc_char = xstrdup_printf ( "t2.acct='root'" ) ;
 user_name = uid_to_string ( ( uid_t ) uid ) ;
 while ( ( row = mysql_fetch_row ( result ) ) ) {
 char * object = xstrdup ( row [ 0 ] ) ;
 if ( ! jobs_running ) {
 list_append ( ret_list , xstrdup ( object ) ) ;
 }
 if ( row [ 1 ] && ( * row [ 1 ] != '\0' ) ) fed_update = true ;
 xfree ( name_char ) ;
 xstrfmtcat ( name_char , "name='%s'" , object ) ;
 xstrfmtcat ( query , "update \"%s_%s\" set time_end=%ld where time_end=0;
" "update \"%s_%s\" set mod_time=%ld, deleted=1;
" "update \"%s_%s\" set mod_time=%ld, deleted=1;
" "update \"%s_%s\" set mod_time=%ld, deleted=1;
" , object , event_table , now , object , cluster_day_table , now , object , cluster_hour_table , now , object , cluster_month_table , now ) ;
 rc = remove_common ( mysql_conn , DBD_REMOVE_CLUSTERS , now , user_name , cluster_table , name_char , assoc_char , object , ret_list , & jobs_running ) ;
 xfree ( object ) ;
 if ( rc != SLURM_SUCCESS ) break ;
 }
 mysql_free_result ( result ) ;
 xfree ( user_name ) ;
 xfree ( name_char ) ;
 xfree ( assoc_char ) ;
 if ( rc != SLURM_SUCCESS ) {
 FREE_NULL_LIST ( ret_list ) ;
 xfree ( query ) ;
 return NULL ;
 }
 if ( ! jobs_running ) {
 if ( debug_flags & DEBUG_FLAG_DB_ASSOC ) DB_DEBUG ( mysql_conn -> conn , "query\n%s" , query ) ;
 rc = mysql_db_query ( mysql_conn , query ) ;
 xfree ( query ) ;
 if ( rc != SLURM_SUCCESS ) {
 reset_mysql_conn ( mysql_conn ) ;
 FREE_NULL_LIST ( ret_list ) ;
 return NULL ;
 }
 memset ( & wckey_cond , 0 , sizeof ( slurmdb_wckey_cond_t ) ) ;
 wckey_cond . cluster_list = ret_list ;
 tmp_list = as_mysql_remove_wckeys ( mysql_conn , uid , & wckey_cond ) ;
 FREE_NULL_LIST ( tmp_list ) ;
 itr = list_iterator_create ( ret_list ) ;
 while ( ( object = list_next ( itr ) ) ) {
 if ( ( rc = remove_cluster_tables ( mysql_conn , object ) ) != SLURM_SUCCESS ) break ;
 cluster_name = xstrdup ( object ) ;
 if ( addto_update_list ( mysql_conn -> update_list , SLURMDB_REMOVE_CLUSTER , cluster_name ) != SLURM_SUCCESS ) xfree ( cluster_name ) ;
 }
 list_iterator_destroy ( itr ) ;
 if ( rc != SLURM_SUCCESS ) {
 reset_mysql_conn ( mysql_conn ) ;
 FREE_NULL_LIST ( ret_list ) ;
 errno = rc ;
 return NULL ;
 }
 if ( fed_update ) as_mysql_add_feds_to_update_list ( mysql_conn ) ;
 errno = SLURM_SUCCESS ;
 }
 else errno = ESLURM_JOBS_RUNNING_ON_ASSOC ;
 xfree ( query ) ;
 return ret_list ;
 }