extern List as_mysql_get_clusters ( mysql_conn_t * mysql_conn , uid_t uid , slurmdb_cluster_cond_t * cluster_cond ) {
 char * query = NULL ;
 char * extra = NULL ;
 char * tmp = NULL ;
 List cluster_list = NULL ;
 ListIterator itr = NULL ;
 int i = 0 ;
 MYSQL_RES * result = NULL ;
 MYSQL_ROW row ;
 slurmdb_assoc_cond_t assoc_cond ;
 ListIterator assoc_itr = NULL ;
 slurmdb_cluster_rec_t * cluster = NULL ;
 slurmdb_assoc_rec_t * assoc = NULL ;
 List assoc_list = NULL ;
 char * cluster_req_inx [ ] = {
 "name" , "classification" , "control_host" , "control_port" , "federation" , "fed_id" , "fed_state" , "fed_weight" , "rpc_version" , "dimensions" , "flags" , "plugin_id_select" }
 ;
 enum {
 CLUSTER_REQ_NAME , CLUSTER_REQ_CLASS , CLUSTER_REQ_CH , CLUSTER_REQ_CP , CLUSTER_REQ_FEDR , CLUSTER_REQ_FEDID , CLUSTER_REQ_FEDSTATE , CLUSTER_REQ_FEDWEIGHT , CLUSTER_REQ_VERSION , CLUSTER_REQ_DIMS , CLUSTER_REQ_FLAGS , CLUSTER_REQ_PI_SELECT , CLUSTER_REQ_COUNT }
 ;
 if ( check_connection ( mysql_conn ) != SLURM_SUCCESS ) return NULL ;
 if ( ! cluster_cond ) {
 xstrcat ( extra , " where deleted=0" ) ;
 goto empty ;
 }
 _setup_cluster_cond_limits ( cluster_cond , & extra ) ;
 empty : xfree ( tmp ) ;
 i = 0 ;
 xstrfmtcat ( tmp , "%s" , cluster_req_inx [ i ] ) ;
 for ( i = 1 ;
 i < CLUSTER_REQ_COUNT ;
 i ++ ) {
 xstrfmtcat ( tmp , ", %s" , cluster_req_inx [ i ] ) ;
 }
 query = xstrdup_printf ( "select %s from %s%s" , tmp , cluster_table , extra ) ;
 xfree ( tmp ) ;
 xfree ( extra ) ;
 if ( debug_flags & DEBUG_FLAG_DB_ASSOC ) DB_DEBUG ( mysql_conn -> conn , "query\n%s" , query ) ;
 if ( ! ( result = mysql_db_query_ret ( mysql_conn , query , 0 ) ) ) {
 xfree ( query ) ;
 return NULL ;
 }
 xfree ( query ) ;
 cluster_list = list_create ( slurmdb_destroy_cluster_rec ) ;
 memset ( & assoc_cond , 0 , sizeof ( slurmdb_assoc_cond_t ) ) ;
 if ( cluster_cond ) {
 assoc_cond . with_deleted = cluster_cond -> with_deleted ;
 }
 assoc_cond . cluster_list = list_create ( NULL ) ;
 while ( ( row = mysql_fetch_row ( result ) ) ) {
 MYSQL_RES * result2 = NULL ;
 MYSQL_ROW row2 ;
 cluster = xmalloc ( sizeof ( slurmdb_cluster_rec_t ) ) ;
 slurmdb_init_cluster_rec ( cluster , 0 ) ;
 list_append ( cluster_list , cluster ) ;
 cluster -> name = xstrdup ( row [ CLUSTER_REQ_NAME ] ) ;
 list_append ( assoc_cond . cluster_list , cluster -> name ) ;
 cluster -> classification = slurm_atoul ( row [ CLUSTER_REQ_CLASS ] ) ;
 cluster -> control_host = xstrdup ( row [ CLUSTER_REQ_CH ] ) ;
 cluster -> control_port = slurm_atoul ( row [ CLUSTER_REQ_CP ] ) ;
 cluster -> fed . name = xstrdup ( row [ CLUSTER_REQ_FEDR ] ) ;
 cluster -> fed . id = slurm_atoul ( row [ CLUSTER_REQ_FEDID ] ) ;
 cluster -> fed . state = slurm_atoul ( row [ CLUSTER_REQ_FEDSTATE ] ) ;
 cluster -> fed . weight = slurm_atoul ( row [ CLUSTER_REQ_FEDWEIGHT ] ) ;
 cluster -> rpc_version = slurm_atoul ( row [ CLUSTER_REQ_VERSION ] ) ;
 cluster -> dimensions = slurm_atoul ( row [ CLUSTER_REQ_DIMS ] ) ;
 cluster -> flags = slurm_atoul ( row [ CLUSTER_REQ_FLAGS ] ) ;
 cluster -> plugin_id_select = slurm_atoul ( row [ CLUSTER_REQ_PI_SELECT ] ) ;
 query = xstrdup_printf ( "select tres, cluster_nodes from " "\"%s_%s\" where time_end=0 and node_name='' limit 1" , cluster -> name , event_table ) ;
 if ( debug_flags & DEBUG_FLAG_DB_TRES ) DB_DEBUG ( mysql_conn -> conn , "query\n%s" , query ) ;
 if ( ! ( result2 = mysql_db_query_ret ( mysql_conn , query , 0 ) ) ) {
 xfree ( query ) ;
 continue ;
 }
 xfree ( query ) ;
 if ( ( row2 = mysql_fetch_row ( result2 ) ) ) {
 cluster -> tres_str = xstrdup ( row2 [ 0 ] ) ;
 if ( row2 [ 1 ] && row2 [ 1 ] [ 0 ] ) cluster -> nodes = xstrdup ( row2 [ 1 ] ) ;
 }
 mysql_free_result ( result2 ) ;
 if ( cluster_cond && cluster_cond -> with_usage ) {
 as_mysql_get_usage ( mysql_conn , uid , cluster , DBD_GET_CLUSTER_USAGE , cluster_cond -> usage_start , cluster_cond -> usage_end ) ;
 }
 }
 mysql_free_result ( result ) ;
 if ( ! list_count ( assoc_cond . cluster_list ) ) {
 FREE_NULL_LIST ( assoc_cond . cluster_list ) ;
 return cluster_list ;
 }
 assoc_cond . acct_list = list_create ( NULL ) ;
 list_append ( assoc_cond . acct_list , "root" ) ;
 assoc_cond . user_list = list_create ( NULL ) ;
 list_append ( assoc_cond . user_list , "" ) ;
 assoc_list = as_mysql_get_assocs ( mysql_conn , uid , & assoc_cond ) ;
 FREE_NULL_LIST ( assoc_cond . cluster_list ) ;
 FREE_NULL_LIST ( assoc_cond . acct_list ) ;
 FREE_NULL_LIST ( assoc_cond . user_list ) ;
 if ( ! assoc_list ) return cluster_list ;
 itr = list_iterator_create ( cluster_list ) ;
 assoc_itr = list_iterator_create ( assoc_list ) ;
 while ( ( cluster = list_next ( itr ) ) ) {
 while ( ( assoc = list_next ( assoc_itr ) ) ) {
 if ( xstrcmp ( assoc -> cluster , cluster -> name ) ) continue ;
 if ( cluster -> root_assoc ) {
 debug ( "This cluster %s already has " "an association." , cluster -> name ) ;
 continue ;
 }
 cluster -> root_assoc = assoc ;
 list_remove ( assoc_itr ) ;
 }
 list_iterator_reset ( assoc_itr ) ;
 }
 list_iterator_destroy ( itr ) ;
 list_iterator_destroy ( assoc_itr ) ;
 if ( list_count ( assoc_list ) ) error ( "I have %d left over associations" , list_count ( assoc_list ) ) ;
 FREE_NULL_LIST ( assoc_list ) ;
 return cluster_list ;
 }