extern int as_mysql_fini_ctld ( mysql_conn_t * mysql_conn , slurmdb_cluster_rec_t * cluster_rec ) {
 int rc = SLURM_SUCCESS ;
 time_t now = time ( NULL ) ;
 char * query = NULL ;
 bool free_it = false ;
 if ( check_connection ( mysql_conn ) != SLURM_SUCCESS ) return ESLURM_DB_CONNECTION ;
 query = xstrdup_printf ( "update %s set mod_time=%ld, control_host='', " "control_port=0 where name='%s' && " "control_host='%s' && control_port=%u;
" , cluster_table , now , cluster_rec -> name , cluster_rec -> control_host , cluster_rec -> control_port ) ;
 if ( debug_flags & DEBUG_FLAG_DB_EVENT ) DB_DEBUG ( mysql_conn -> conn , "query\n%s" , query ) ;
 rc = mysql_db_query ( mysql_conn , query ) ;
 xfree ( query ) ;
 if ( rc != SLURM_SUCCESS ) return SLURM_ERROR ;
 if ( ! last_affected_rows ( mysql_conn ) || ( slurmdbd_conf && ! slurmdbd_conf -> track_ctld ) ) return rc ;
 if ( ! cluster_rec -> tres_str ) {
 free_it = true ;
 as_mysql_cluster_tres ( mysql_conn , cluster_rec -> control_host , & cluster_rec -> tres_str , now ) ;
 }
 if ( ! cluster_rec -> tres_str ) return rc ;
 query = xstrdup_printf ( "insert into \"%s_%s\" (tres, state, time_start, reason) " "values ('%s', %u, %ld, 'slurmctld disconnect');
" , cluster_rec -> name , event_table , cluster_rec -> tres_str , NODE_STATE_DOWN , ( long ) now ) ;
 if ( free_it ) xfree ( cluster_rec -> tres_str ) ;
 if ( debug_flags & DEBUG_FLAG_DB_EVENT ) DB_DEBUG ( mysql_conn -> conn , "query\n%s" , query ) ;
 rc = mysql_db_query ( mysql_conn , query ) ;
 xfree ( query ) ;
 return rc ;
 }