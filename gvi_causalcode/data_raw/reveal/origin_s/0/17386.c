extern List as_mysql_get_resvs ( mysql_conn_t * mysql_conn , uid_t uid , slurmdb_reservation_cond_t * resv_cond ) {
 char * query = NULL ;
 char * extra = NULL ;
 char * tmp = NULL ;
 List resv_list = NULL ;
 int i = 0 , is_admin = 1 ;
 MYSQL_RES * result = NULL ;
 MYSQL_ROW row ;
 uint16_t private_data = 0 ;
 slurmdb_job_cond_t job_cond ;
 void * curr_cluster = NULL ;
 List local_cluster_list = NULL ;
 List use_cluster_list = as_mysql_cluster_list ;
 ListIterator itr = NULL ;
 char * cluster_name = NULL ;
 uint16_t with_usage = 0 ;
 char * resv_req_inx [ ] = {
 "id_resv" , "assoclist" , "flags" , "nodelist" , "node_inx" , "resv_name" , "time_start" , "time_end" , "tres" }
 ;
 enum {
 RESV_REQ_ID , RESV_REQ_ASSOCS , RESV_REQ_FLAGS , RESV_REQ_NODES , RESV_REQ_NODE_INX , RESV_REQ_NAME , RESV_REQ_START , RESV_REQ_END , RESV_REQ_TRES , RESV_REQ_COUNT }
 ;
 if ( ! resv_cond ) {
 xstrcat ( extra , " where deleted=0" ) ;
 goto empty ;
 }
 if ( check_connection ( mysql_conn ) != SLURM_SUCCESS ) return NULL ;
 private_data = slurm_get_private_data ( ) ;
 if ( private_data & PRIVATE_DATA_RESERVATIONS ) {
 if ( ! ( is_admin = is_user_min_admin_level ( mysql_conn , uid , SLURMDB_ADMIN_OPERATOR ) ) ) {
 error ( "Only admins can look at reservations" ) ;
 errno = ESLURM_ACCESS_DENIED ;
 return NULL ;
 }
 }
 memset ( & job_cond , 0 , sizeof ( slurmdb_job_cond_t ) ) ;
 if ( resv_cond -> nodes ) {
 job_cond . usage_start = resv_cond -> time_start ;
 job_cond . usage_end = resv_cond -> time_end ;
 job_cond . used_nodes = resv_cond -> nodes ;
 job_cond . cluster_list = resv_cond -> cluster_list ;
 local_cluster_list = setup_cluster_list_with_inx ( mysql_conn , & job_cond , ( void * * ) & curr_cluster ) ;
 }
 else if ( with_usage ) {
 job_cond . usage_start = resv_cond -> time_start ;
 job_cond . usage_end = resv_cond -> time_end ;
 }
 ( void ) _setup_resv_cond_limits ( resv_cond , & extra ) ;
 with_usage = resv_cond -> with_usage ;
 if ( resv_cond -> cluster_list && list_count ( resv_cond -> cluster_list ) ) use_cluster_list = resv_cond -> cluster_list ;
 empty : xfree ( tmp ) ;
 xstrfmtcat ( tmp , "t1.%s" , resv_req_inx [ i ] ) ;
 for ( i = 1 ;
 i < RESV_REQ_COUNT ;
 i ++ ) {
 xstrfmtcat ( tmp , ", t1.%s" , resv_req_inx [ i ] ) ;
 }
 if ( use_cluster_list == as_mysql_cluster_list ) slurm_mutex_lock ( & as_mysql_cluster_list_lock ) ;
 itr = list_iterator_create ( use_cluster_list ) ;
 while ( ( cluster_name = list_next ( itr ) ) ) {
 if ( query ) xstrcat ( query , " union " ) ;
 xstrfmtcat ( query , "select distinct %s,'%s' as cluster " "from \"%s_%s\" as t1%s" , tmp , cluster_name , cluster_name , resv_table , extra ? extra : "" ) ;
 }
 list_iterator_destroy ( itr ) ;
 if ( use_cluster_list == as_mysql_cluster_list ) slurm_mutex_unlock ( & as_mysql_cluster_list_lock ) ;
 if ( query ) xstrcat ( query , " order by cluster, resv_name;
" ) ;
 xfree ( tmp ) ;
 xfree ( extra ) ;
 if ( debug_flags & DEBUG_FLAG_DB_RESV ) DB_DEBUG ( mysql_conn -> conn , "query\n%s" , query ) ;
 if ( ! ( result = mysql_db_query_ret ( mysql_conn , query , 0 ) ) ) {
 xfree ( query ) ;
 FREE_NULL_LIST ( local_cluster_list ) ;
 return NULL ;
 }
 xfree ( query ) ;
 resv_list = list_create ( slurmdb_destroy_reservation_rec ) ;
 while ( ( row = mysql_fetch_row ( result ) ) ) {
 slurmdb_reservation_rec_t * resv = xmalloc ( sizeof ( slurmdb_reservation_rec_t ) ) ;
 int start = slurm_atoul ( row [ RESV_REQ_START ] ) ;
 list_append ( resv_list , resv ) ;
 if ( ! good_nodes_from_inx ( local_cluster_list , & curr_cluster , row [ RESV_REQ_NODE_INX ] , start ) ) continue ;
 resv -> id = slurm_atoul ( row [ RESV_REQ_ID ] ) ;
 if ( with_usage ) {
 if ( ! job_cond . resvid_list ) job_cond . resvid_list = list_create ( NULL ) ;
 list_append ( job_cond . resvid_list , row [ RESV_REQ_ID ] ) ;
 }
 resv -> name = xstrdup ( row [ RESV_REQ_NAME ] ) ;
 resv -> cluster = xstrdup ( row [ RESV_REQ_COUNT ] ) ;
 resv -> assocs = xstrdup ( row [ RESV_REQ_ASSOCS ] ) ;
 resv -> nodes = xstrdup ( row [ RESV_REQ_NODES ] ) ;
 resv -> time_start = start ;
 resv -> time_end = slurm_atoul ( row [ RESV_REQ_END ] ) ;
 resv -> flags = slurm_atoul ( row [ RESV_REQ_FLAGS ] ) ;
 resv -> tres_str = xstrdup ( row [ RESV_REQ_TRES ] ) ;
 }
 FREE_NULL_LIST ( local_cluster_list ) ;
 if ( with_usage && resv_list && list_count ( resv_list ) ) {
 List job_list = as_mysql_jobacct_process_get_jobs ( mysql_conn , uid , & job_cond ) ;
 ListIterator itr = NULL , itr2 = NULL ;
 slurmdb_job_rec_t * job = NULL ;
 slurmdb_reservation_rec_t * resv = NULL ;
 if ( ! job_list || ! list_count ( job_list ) ) goto no_jobs ;
 itr = list_iterator_create ( job_list ) ;
 itr2 = list_iterator_create ( resv_list ) ;
 while ( ( job = list_next ( itr ) ) ) {
 int set = 0 ;
 while ( ( resv = list_next ( itr2 ) ) ) {
 int start = job -> start ;
 int end = job -> end ;
 int elapsed = 0 ;
 if ( resv -> id != job -> resvid ) continue ;
 set = 1 ;
 if ( start < resv -> time_start ) start = resv -> time_start ;
 if ( ! end || end > resv -> time_end ) end = resv -> time_end ;
 if ( ( elapsed = ( end - start ) ) < 1 ) continue ;
 slurmdb_transfer_tres_time ( & resv -> tres_list , job -> tres_alloc_str , elapsed ) ;
 }
 list_iterator_reset ( itr2 ) ;
 if ( ! set ) {
 error ( "we got a job %u with no reservation " "associatied with it?" , job -> jobid ) ;
 }
 }
 list_iterator_destroy ( itr2 ) ;
 list_iterator_destroy ( itr ) ;
 no_jobs : FREE_NULL_LIST ( job_list ) ;
 }
 FREE_NULL_LIST ( job_cond . resvid_list ) ;
 mysql_free_result ( result ) ;
 return resv_list ;
 }