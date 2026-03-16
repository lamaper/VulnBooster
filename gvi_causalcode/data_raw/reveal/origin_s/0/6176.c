extern int as_mysql_modify_resv ( mysql_conn_t * mysql_conn , slurmdb_reservation_rec_t * resv ) {
 MYSQL_RES * result = NULL ;
 MYSQL_ROW row ;
 int rc = SLURM_SUCCESS ;
 char * cols = NULL , * vals = NULL , * extra = NULL , * query = NULL ;
 time_t start = 0 , now = time ( NULL ) ;
 int i ;
 int set = 0 ;
 char * resv_req_inx [ ] = {
 "assoclist" , "time_start" , "time_end" , "resv_name" , "nodelist" , "node_inx" , "flags" , "tres" }
 ;
 enum {
 RESV_ASSOCS , RESV_START , RESV_END , RESV_NAME , RESV_NODES , RESV_NODE_INX , RESV_FLAGS , RESV_TRES , RESV_COUNT }
 ;
 if ( ! resv ) {
 error ( "No reservation was given to edit" ) ;
 return SLURM_ERROR ;
 }
 if ( ! resv -> id ) {
 error ( "We need an id to edit a reservation." ) ;
 return SLURM_ERROR ;
 }
 if ( ! resv -> time_start ) {
 error ( "We need a start time to edit a reservation." ) ;
 return SLURM_ERROR ;
 }
 if ( ! resv -> cluster || ! resv -> cluster [ 0 ] ) {
 error ( "We need a cluster name to edit a reservation." ) ;
 return SLURM_ERROR ;
 }
 if ( ! resv -> time_start_prev ) {
 error ( "We need a time to check for last " "start of reservation." ) ;
 return SLURM_ERROR ;
 }
 xstrfmtcat ( cols , "%s" , resv_req_inx [ 0 ] ) ;
 for ( i = 1 ;
 i < RESV_COUNT ;
 i ++ ) {
 xstrfmtcat ( cols , ", %s" , resv_req_inx [ i ] ) ;
 }
 query = xstrdup_printf ( "select %s from \"%s_%s\" where id_resv=%u " "and (time_start=%ld || time_start=%ld) " "and deleted=0 order by time_start desc " "limit 1 FOR UPDATE;
" , cols , resv -> cluster , resv_table , resv -> id , resv -> time_start , resv -> time_start_prev ) ;
 try_again : debug4 ( "%d(%s:%d) query\n%s" , mysql_conn -> conn , THIS_FILE , __LINE__ , query ) ;
 if ( ! ( result = mysql_db_query_ret ( mysql_conn , query , 0 ) ) ) {
 rc = SLURM_ERROR ;
 goto end_it ;
 }
 if ( ! ( row = mysql_fetch_row ( result ) ) ) {
 rc = SLURM_ERROR ;
 mysql_free_result ( result ) ;
 error ( "There is no reservation by id %u, " "time_start %ld, and cluster '%s'" , resv -> id , resv -> time_start_prev , resv -> cluster ) ;
 if ( ! set && resv -> time_end ) {
 xfree ( query ) ;
 query = xstrdup_printf ( "select %s from \"%s_%s\" where id_resv=%u " "and time_start <= %ld and deleted=0 " "order by time_start desc " "limit 1;
" , cols , resv -> cluster , resv_table , resv -> id , resv -> time_end ) ;
 set = 1 ;
 goto try_again ;
 }
 goto end_it ;
 }
 start = slurm_atoul ( row [ RESV_START ] ) ;
 xfree ( query ) ;
 xfree ( cols ) ;
 set = 0 ;
 if ( ! resv -> name && row [ RESV_NAME ] && row [ RESV_NAME ] [ 0 ] ) resv -> name = xstrdup ( row [ RESV_NAME ] ) ;
 if ( resv -> assocs ) set = 1 ;
 else if ( row [ RESV_ASSOCS ] && row [ RESV_ASSOCS ] [ 0 ] ) resv -> assocs = xstrdup ( row [ RESV_ASSOCS ] ) ;
 if ( resv -> flags != NO_VAL ) set = 1 ;
 else resv -> flags = slurm_atoul ( row [ RESV_FLAGS ] ) ;
 if ( resv -> nodes ) set = 1 ;
 else if ( row [ RESV_NODES ] && row [ RESV_NODES ] [ 0 ] ) {
 resv -> nodes = xstrdup ( row [ RESV_NODES ] ) ;
 resv -> node_inx = xstrdup ( row [ RESV_NODE_INX ] ) ;
 }
 if ( ! resv -> time_end ) resv -> time_end = slurm_atoul ( row [ RESV_END ] ) ;
 if ( resv -> tres_str ) set = 1 ;
 else if ( row [ RESV_TRES ] && row [ RESV_TRES ] [ 0 ] ) resv -> tres_str = xstrdup ( row [ RESV_TRES ] ) ;
 mysql_free_result ( result ) ;
 _setup_resv_limits ( resv , & cols , & vals , & extra ) ;
 if ( ( start > now ) || ! set ) {
 query = xstrdup_printf ( "update \"%s_%s\" set deleted=0%s " "where deleted=0 and id_resv=%u " "and time_start=%ld;
" , resv -> cluster , resv_table , extra , resv -> id , start ) ;
 }
 else {
 query = xstrdup_printf ( "update \"%s_%s\" set time_end=%ld " "where deleted=0 && id_resv=%u " "and time_start=%ld;
" , resv -> cluster , resv_table , resv -> time_start - 1 , resv -> id , start ) ;
 xstrfmtcat ( query , "insert into \"%s_%s\" (id_resv%s) " "values (%u%s) " "on duplicate key update deleted=0%s;
" , resv -> cluster , resv_table , cols , resv -> id , vals , extra ) ;
 }
 if ( debug_flags & DEBUG_FLAG_DB_RESV ) DB_DEBUG ( mysql_conn -> conn , "query\n%s" , query ) ;
 rc = mysql_db_query ( mysql_conn , query ) ;
 end_it : xfree ( query ) ;
 xfree ( cols ) ;
 xfree ( vals ) ;
 xfree ( extra ) ;
 return rc ;
 }