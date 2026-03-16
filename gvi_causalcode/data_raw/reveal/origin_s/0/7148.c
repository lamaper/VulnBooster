extern int as_mysql_add_resv ( mysql_conn_t * mysql_conn , slurmdb_reservation_rec_t * resv ) {
 int rc = SLURM_SUCCESS ;
 char * cols = NULL , * vals = NULL , * extra = NULL , * query = NULL ;
 if ( ! resv ) {
 error ( "No reservation was given to add." ) ;
 return SLURM_ERROR ;
 }
 if ( ! resv -> id ) {
 error ( "We need an id to add a reservation." ) ;
 return SLURM_ERROR ;
 }
 if ( ! resv -> time_start ) {
 error ( "We need a start time to add a reservation." ) ;
 return SLURM_ERROR ;
 }
 if ( ! resv -> cluster || ! resv -> cluster [ 0 ] ) {
 error ( "We need a cluster name to add a reservation." ) ;
 return SLURM_ERROR ;
 }
 _setup_resv_limits ( resv , & cols , & vals , & extra ) ;
 xstrfmtcat ( query , "insert into \"%s_%s\" (id_resv%s) values (%u%s) " "on duplicate key update deleted=0%s;
" , resv -> cluster , resv_table , cols , resv -> id , vals , extra ) ;
 if ( debug_flags & DEBUG_FLAG_DB_RESV ) DB_DEBUG ( mysql_conn -> conn , "query\n%s" , query ) ;
 rc = mysql_db_query ( mysql_conn , query ) ;
 xfree ( query ) ;
 xfree ( cols ) ;
 xfree ( vals ) ;
 xfree ( extra ) ;
 return rc ;
 }