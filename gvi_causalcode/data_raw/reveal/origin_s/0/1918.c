extern int as_mysql_cluster_tres ( mysql_conn_t * mysql_conn , char * cluster_nodes , char * * tres_str_in , time_t event_time ) {
 char * query ;
 int rc = SLURM_SUCCESS ;
 int first = 0 ;
 MYSQL_RES * result = NULL ;
 MYSQL_ROW row ;
 xassert ( tres_str_in ) ;
 if ( check_connection ( mysql_conn ) != SLURM_SUCCESS ) return ESLURM_DB_CONNECTION ;
 if ( ! mysql_conn -> cluster_name ) {
 error ( "%s:%d no cluster name" , THIS_FILE , __LINE__ ) ;
 return SLURM_ERROR ;
 }
 query = xstrdup_printf ( "select tres, cluster_nodes from \"%s_%s\" where " "time_end=0 and node_name='' and state=0 limit 1" , mysql_conn -> cluster_name , event_table ) ;
 if ( ! ( result = mysql_db_query_ret ( mysql_conn , query , 0 ) ) ) {
 xfree ( query ) ;
 if ( mysql_errno ( mysql_conn -> db_conn ) == ER_NO_SUCH_TABLE ) rc = ESLURM_ACCESS_DENIED ;
 else rc = SLURM_ERROR ;
 return rc ;
 }
 xfree ( query ) ;
 if ( ! ( row = mysql_fetch_row ( result ) ) ) {
 debug ( "We don't have an entry for this machine %s " "most likely a first time running." , mysql_conn -> cluster_name ) ;
 if ( ! * tres_str_in ) {
 rc = 0 ;
 goto end_it ;
 }
 first = 1 ;
 goto add_it ;
 }
 if ( ! * tres_str_in ) {
 * tres_str_in = xstrdup ( row [ 0 ] ) ;
 goto end_it ;
 }
 else if ( xstrcmp ( * tres_str_in , row [ 0 ] ) ) {
 debug ( "%s has changed tres from %s to %s" , mysql_conn -> cluster_name , row [ 0 ] , * tres_str_in ) ;
 }
 else {
 if ( debug_flags & DEBUG_FLAG_DB_EVENT ) DB_DEBUG ( mysql_conn -> conn , "We have the same tres as before for %s, " "no need to update the database." , mysql_conn -> cluster_name ) ;
 if ( cluster_nodes ) {
 if ( ! row [ 1 ] [ 0 ] ) {
 debug ( "Adding cluster nodes '%s' to " "last instance of cluster '%s'." , cluster_nodes , mysql_conn -> cluster_name ) ;
 query = xstrdup_printf ( "update \"%s_%s\" set " "cluster_nodes='%s' " "where time_end=0 and node_name=''" , mysql_conn -> cluster_name , event_table , cluster_nodes ) ;
 ( void ) mysql_db_query ( mysql_conn , query ) ;
 xfree ( query ) ;
 goto update_it ;
 }
 else if ( ! xstrcmp ( cluster_nodes , row [ 1 ] ) ) {
 if ( debug_flags & DEBUG_FLAG_DB_EVENT ) DB_DEBUG ( mysql_conn -> conn , "we have the same nodes " "in the cluster " "as before no need to " "update the database." ) ;
 goto update_it ;
 }
 }
 goto end_it ;
 }
 query = xstrdup_printf ( "update \"%s_%s\" set time_end=%ld where time_end=0" , mysql_conn -> cluster_name , event_table , event_time ) ;
 rc = mysql_db_query ( mysql_conn , query ) ;
 xfree ( query ) ;
 first = 1 ;
 if ( rc != SLURM_SUCCESS ) goto end_it ;
 add_it : query = xstrdup_printf ( "insert into \"%s_%s\" (cluster_nodes, tres, " "time_start, reason) " "values ('%s', '%s', %ld, 'Cluster Registered TRES');
" , mysql_conn -> cluster_name , event_table , cluster_nodes , * tres_str_in , event_time ) ;
 ( void ) mysql_db_query ( mysql_conn , query ) ;
 xfree ( query ) ;
 update_it : query = xstrdup_printf ( "update \"%s_%s\" set time_end=%ld where time_end=0 " "and state=%u and node_name='';
" , mysql_conn -> cluster_name , event_table , event_time , NODE_STATE_DOWN ) ;
 rc = mysql_db_query ( mysql_conn , query ) ;
 xfree ( query ) ;
 end_it : mysql_free_result ( result ) ;
 if ( first && rc == SLURM_SUCCESS ) rc = ACCOUNTING_FIRST_REG ;
 return rc ;
 }