extern int as_mysql_remove_resv ( mysql_conn_t * mysql_conn , slurmdb_reservation_rec_t * resv ) {
 int rc = SLURM_SUCCESS ;
 char * query = NULL ;
 if ( ! resv ) {
 error ( "No reservation was given to remove" ) ;
 return SLURM_ERROR ;
 }
 if ( ! resv -> id ) {
 error ( "An id is needed to remove a reservation." ) ;
 return SLURM_ERROR ;
 }
 if ( ! resv -> time_start ) {
 error ( "A start time is needed to remove a reservation." ) ;
 return SLURM_ERROR ;
 }
 if ( ! resv -> cluster || ! resv -> cluster [ 0 ] ) {
 error ( "A cluster name is needed to remove a reservation." ) ;
 return SLURM_ERROR ;
 }
 query = xstrdup_printf ( "delete from \"%s_%s\" where time_start > %ld " "and id_resv=%u and time_start=%ld;
" , resv -> cluster , resv_table , resv -> time_start_prev , resv -> id , resv -> time_start ) ;
 xstrfmtcat ( query , "update \"%s_%s\" set time_end=%ld, " "deleted=1 where deleted=0 and " "id_resv=%u and time_start=%ld;
" , resv -> cluster , resv_table , resv -> time_start_prev , resv -> id , resv -> time_start ) ;
 if ( debug_flags & DEBUG_FLAG_DB_RESV ) DB_DEBUG ( mysql_conn -> conn , "query\n%s" , query ) ;
 rc = mysql_db_query ( mysql_conn , query ) ;
 xfree ( query ) ;
 return rc ;
 }