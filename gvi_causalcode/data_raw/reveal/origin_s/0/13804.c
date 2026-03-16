extern List as_mysql_get_cluster_events ( mysql_conn_t * mysql_conn , uint32_t uid , slurmdb_event_cond_t * event_cond ) {
 char * query = NULL ;
 char * extra = NULL ;
 char * tmp = NULL ;
 List ret_list = NULL ;
 ListIterator itr = NULL ;
 char * object = NULL ;
 int set = 0 ;
 int i = 0 ;
 MYSQL_RES * result = NULL ;
 MYSQL_ROW row ;
 time_t now = time ( NULL ) ;
 List use_cluster_list = as_mysql_cluster_list ;
 char * event_req_inx [ ] = {
 "cluster_nodes" , "node_name" , "state" , "time_start" , "time_end" , "reason" , "reason_uid" , "tres" , }
 ;
 enum {
 EVENT_REQ_CNODES , EVENT_REQ_NODE , EVENT_REQ_STATE , EVENT_REQ_START , EVENT_REQ_END , EVENT_REQ_REASON , EVENT_REQ_REASON_UID , EVENT_REQ_TRES , EVENT_REQ_COUNT }
 ;
 if ( check_connection ( mysql_conn ) != SLURM_SUCCESS ) return NULL ;
 if ( ! event_cond ) goto empty ;
 if ( event_cond -> cpus_min ) {
 if ( extra ) xstrcat ( extra , " && (" ) ;
 else xstrcat ( extra , " where (" ) ;
 if ( event_cond -> cpus_max ) {
 xstrfmtcat ( extra , "count between %u and %u)" , event_cond -> cpus_min , event_cond -> cpus_max ) ;
 }
 else {
 xstrfmtcat ( extra , "count='%u')" , event_cond -> cpus_min ) ;
 }
 }
 switch ( event_cond -> event_type ) {
 case SLURMDB_EVENT_ALL : break ;
 case SLURMDB_EVENT_CLUSTER : if ( extra ) xstrcat ( extra , " && (" ) ;
 else xstrcat ( extra , " where (" ) ;
 xstrcat ( extra , "node_name = '')" ) ;
 break ;
 case SLURMDB_EVENT_NODE : if ( extra ) xstrcat ( extra , " && (" ) ;
 else xstrcat ( extra , " where (" ) ;
 xstrcat ( extra , "node_name != '')" ) ;
 break ;
 default : error ( "Unknown event %u doing all" , event_cond -> event_type ) ;
 break ;
 }
 if ( event_cond -> node_list && list_count ( event_cond -> node_list ) ) {
 set = 0 ;
 if ( extra ) xstrcat ( extra , " && (" ) ;
 else xstrcat ( extra , " where (" ) ;
 itr = list_iterator_create ( event_cond -> node_list ) ;
 while ( ( object = list_next ( itr ) ) ) {
 if ( set ) xstrcat ( extra , " || " ) ;
 xstrfmtcat ( extra , "node_name='%s'" , object ) ;
 set = 1 ;
 }
 list_iterator_destroy ( itr ) ;
 xstrcat ( extra , ")" ) ;
 }
 if ( event_cond -> period_start ) {
 if ( ! event_cond -> period_end ) event_cond -> period_end = now ;
 if ( extra ) xstrcat ( extra , " && (" ) ;
 else xstrcat ( extra , " where (" ) ;
 xstrfmtcat ( extra , "(time_start < %ld) " "&& (time_end >= %ld || time_end = 0))" , event_cond -> period_end , event_cond -> period_start ) ;
 }
 if ( event_cond -> reason_list && list_count ( event_cond -> reason_list ) ) {
 set = 0 ;
 if ( extra ) xstrcat ( extra , " && (" ) ;
 else xstrcat ( extra , " where (" ) ;
 itr = list_iterator_create ( event_cond -> reason_list ) ;
 while ( ( object = list_next ( itr ) ) ) {
 if ( set ) xstrcat ( extra , " || " ) ;
 xstrfmtcat ( extra , "reason like '%%%s%%'" , object ) ;
 set = 1 ;
 }
 list_iterator_destroy ( itr ) ;
 xstrcat ( extra , ")" ) ;
 }
 if ( event_cond -> reason_uid_list && list_count ( event_cond -> reason_uid_list ) ) {
 set = 0 ;
 if ( extra ) xstrcat ( extra , " && (" ) ;
 else xstrcat ( extra , " where (" ) ;
 itr = list_iterator_create ( event_cond -> reason_uid_list ) ;
 while ( ( object = list_next ( itr ) ) ) {
 if ( set ) xstrcat ( extra , " || " ) ;
 xstrfmtcat ( extra , "reason_uid='%s'" , object ) ;
 set = 1 ;
 }
 list_iterator_destroy ( itr ) ;
 xstrcat ( extra , ")" ) ;
 }
 if ( event_cond -> state_list && list_count ( event_cond -> state_list ) ) {
 set = 0 ;
 if ( extra ) xstrcat ( extra , " && (" ) ;
 else xstrcat ( extra , " where (" ) ;
 itr = list_iterator_create ( event_cond -> state_list ) ;
 while ( ( object = list_next ( itr ) ) ) {
 if ( set ) xstrcat ( extra , " || " ) ;
 xstrfmtcat ( extra , "state='%s'" , object ) ;
 set = 1 ;
 }
 list_iterator_destroy ( itr ) ;
 xstrcat ( extra , ")" ) ;
 }
 if ( event_cond -> cluster_list && list_count ( event_cond -> cluster_list ) ) use_cluster_list = event_cond -> cluster_list ;
 empty : xfree ( tmp ) ;
 xstrfmtcat ( tmp , "%s" , event_req_inx [ 0 ] ) ;
 for ( i = 1 ;
 i < EVENT_REQ_COUNT ;
 i ++ ) {
 xstrfmtcat ( tmp , ", %s" , event_req_inx [ i ] ) ;
 }
 if ( use_cluster_list == as_mysql_cluster_list ) slurm_mutex_lock ( & as_mysql_cluster_list_lock ) ;
 ret_list = list_create ( slurmdb_destroy_event_rec ) ;
 itr = list_iterator_create ( use_cluster_list ) ;
 while ( ( object = list_next ( itr ) ) ) {
 query = xstrdup_printf ( "select %s from \"%s_%s\"" , tmp , object , event_table ) ;
 if ( extra ) xstrfmtcat ( query , " %s" , extra ) ;
 if ( debug_flags & DEBUG_FLAG_DB_ASSOC ) DB_DEBUG ( mysql_conn -> conn , "query\n%s" , query ) ;
 if ( ! ( result = mysql_db_query_ret ( mysql_conn , query , 0 ) ) ) {
 xfree ( query ) ;
 if ( mysql_errno ( mysql_conn -> db_conn ) != ER_NO_SUCH_TABLE ) {
 FREE_NULL_LIST ( ret_list ) ;
 ret_list = NULL ;
 }
 break ;
 }
 xfree ( query ) ;
 while ( ( row = mysql_fetch_row ( result ) ) ) {
 slurmdb_event_rec_t * event = xmalloc ( sizeof ( slurmdb_event_rec_t ) ) ;
 list_append ( ret_list , event ) ;
 event -> cluster = xstrdup ( object ) ;
 if ( row [ EVENT_REQ_NODE ] && row [ EVENT_REQ_NODE ] [ 0 ] ) {
 event -> node_name = xstrdup ( row [ EVENT_REQ_NODE ] ) ;
 event -> event_type = SLURMDB_EVENT_NODE ;
 }
 else event -> event_type = SLURMDB_EVENT_CLUSTER ;
 event -> state = slurm_atoul ( row [ EVENT_REQ_STATE ] ) ;
 event -> period_start = slurm_atoul ( row [ EVENT_REQ_START ] ) ;
 event -> period_end = slurm_atoul ( row [ EVENT_REQ_END ] ) ;
 if ( row [ EVENT_REQ_REASON ] && row [ EVENT_REQ_REASON ] [ 0 ] ) event -> reason = xstrdup ( row [ EVENT_REQ_REASON ] ) ;
 event -> reason_uid = slurm_atoul ( row [ EVENT_REQ_REASON_UID ] ) ;
 if ( row [ EVENT_REQ_CNODES ] && row [ EVENT_REQ_CNODES ] [ 0 ] ) event -> cluster_nodes = xstrdup ( row [ EVENT_REQ_CNODES ] ) ;
 if ( row [ EVENT_REQ_TRES ] && row [ EVENT_REQ_TRES ] [ 0 ] ) event -> tres_str = xstrdup ( row [ EVENT_REQ_TRES ] ) ;
 }
 mysql_free_result ( result ) ;
 }
 list_iterator_destroy ( itr ) ;
 xfree ( tmp ) ;
 xfree ( extra ) ;
 if ( use_cluster_list == as_mysql_cluster_list ) slurm_mutex_unlock ( & as_mysql_cluster_list_lock ) ;
 return ret_list ;
 }