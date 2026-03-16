extern int as_mysql_node_up ( mysql_conn_t * mysql_conn , struct node_record * node_ptr , time_t event_time ) {
 char * query ;
 int rc = SLURM_SUCCESS ;
 if ( check_connection ( mysql_conn ) != SLURM_SUCCESS ) return ESLURM_DB_CONNECTION ;
 if ( ! mysql_conn -> cluster_name ) {
 error ( "%s:%d no cluster name" , THIS_FILE , __LINE__ ) ;
 return SLURM_ERROR ;
 }
 query = xstrdup_printf ( "update \"%s_%s\" set time_end=%ld where " "time_end=0 and node_name='%s';
" , mysql_conn -> cluster_name , event_table , event_time , node_ptr -> name ) ;
 debug4 ( "%d(%s:%d) query\n%s" , mysql_conn -> conn , THIS_FILE , __LINE__ , query ) ;
 rc = mysql_db_query ( mysql_conn , query ) ;
 xfree ( query ) ;
 return rc ;
 }