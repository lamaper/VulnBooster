extern int as_mysql_add_clusters ( mysql_conn_t * mysql_conn , uint32_t uid , List cluster_list ) {
 ListIterator itr = NULL ;
 int rc = SLURM_SUCCESS ;
 slurmdb_cluster_rec_t * object = NULL ;
 char * cols = NULL , * vals = NULL , * extra = NULL , * query = NULL , * tmp_extra = NULL ;
 time_t now = time ( NULL ) ;
 char * user_name = NULL ;
 int affect_rows = 0 ;
 int added = 0 ;
 bool has_feds = false ;
 List assoc_list = NULL ;
 slurmdb_assoc_rec_t * assoc = NULL ;
 if ( check_connection ( mysql_conn ) != SLURM_SUCCESS ) return ESLURM_DB_CONNECTION ;
 if ( ! is_user_min_admin_level ( mysql_conn , uid , SLURMDB_ADMIN_SUPER_USER ) ) return ESLURM_ACCESS_DENIED ;
 assoc_list = list_create ( slurmdb_destroy_assoc_rec ) ;
 user_name = uid_to_string ( ( uid_t ) uid ) ;
 itr = list_iterator_create ( cluster_list ) ;
 while ( ( object = list_next ( itr ) ) ) {
 if ( ! object -> name || ! object -> name [ 0 ] ) {
 error ( "We need a cluster name to add." ) ;
 rc = SLURM_ERROR ;
 list_remove ( itr ) ;
 continue ;
 }
 if ( ( rc = create_cluster_tables ( mysql_conn , object -> name ) ) != SLURM_SUCCESS ) {
 xfree ( extra ) ;
 xfree ( cols ) ;
 xfree ( vals ) ;
 added = 0 ;
 if ( mysql_errno ( mysql_conn -> db_conn ) == ER_WRONG_TABLE_NAME ) rc = ESLURM_BAD_NAME ;
 goto end_it ;
 }
 }
 list_iterator_reset ( itr ) ;
 while ( ( object = list_next ( itr ) ) ) {
 int fed_id = 0 ;
 uint16_t fed_state = CLUSTER_FED_STATE_NA ;
 uint32_t fed_weight = 1 ;
 xstrcat ( cols , "creation_time, mod_time, acct" ) ;
 xstrfmtcat ( vals , "%ld, %ld, 'root'" , now , now ) ;
 xstrfmtcat ( extra , ", mod_time=%ld" , now ) ;
 if ( object -> root_assoc ) setup_assoc_limits ( object -> root_assoc , & cols , & vals , & extra , QOS_LEVEL_SET , 1 ) ;
 if ( object -> fed . name ) {
 has_feds = 1 ;
 rc = as_mysql_get_fed_cluster_id ( mysql_conn , object -> name , object -> fed . name , - 1 , & fed_id ) ;
 if ( rc ) {
 error ( "failed to get cluster id for " "federation" ) ;
 xfree ( extra ) ;
 xfree ( cols ) ;
 xfree ( vals ) ;
 added = 0 ;
 goto end_it ;
 }
 if ( object -> fed . state != NO_VAL ) fed_state = object -> fed . state ;
 else fed_state = CLUSTER_FED_STATE_ACTIVE ;
 }
 if ( object -> fed . weight != NO_VAL ) fed_weight = object -> fed . weight ;
 xstrfmtcat ( query , "insert into %s (creation_time, mod_time, " "name, classification, federation, fed_id, " "fed_state, fed_weight) " "values (%ld, %ld, '%s', %u, '%s', %d, %u, %u) " "on duplicate key update deleted=0, mod_time=%ld, " "control_host='', control_port=0, " "classification=%u, flags=0, federation='%s', " "fed_id=%d, fed_state=%u, fed_weight=%u" , cluster_table , now , now , object -> name , object -> classification , ( object -> fed . name ) ? object -> fed . name : "" , fed_id , fed_state , fed_weight , now , object -> classification , ( object -> fed . name ) ? object -> fed . name : "" , fed_id , fed_state , fed_weight ) ;
 if ( debug_flags & DEBUG_FLAG_DB_ASSOC ) DB_DEBUG ( mysql_conn -> conn , "query\n%s" , query ) ;
 rc = mysql_db_query ( mysql_conn , query ) ;
 xfree ( query ) ;
 if ( rc != SLURM_SUCCESS ) {
 error ( "Couldn't add cluster %s" , object -> name ) ;
 xfree ( extra ) ;
 xfree ( cols ) ;
 xfree ( vals ) ;
 added = 0 ;
 break ;
 }
 affect_rows = last_affected_rows ( mysql_conn ) ;
 if ( ! affect_rows ) {
 debug2 ( "nothing changed %d" , affect_rows ) ;
 xfree ( extra ) ;
 xfree ( cols ) ;
 xfree ( vals ) ;
 continue ;
 }
 xstrfmtcat ( query , "insert into \"%s_%s\" (%s, lft, rgt) " "values (%s, 1, 2) " "on duplicate key update deleted=0, " "id_assoc=LAST_INSERT_ID(id_assoc)%s;
" , object -> name , assoc_table , cols , vals , extra ) ;
 xfree ( cols ) ;
 xfree ( vals ) ;
 if ( debug_flags & DEBUG_FLAG_DB_ASSOC ) DB_DEBUG ( mysql_conn -> conn , "query\n%s" , query ) ;
 rc = mysql_db_query ( mysql_conn , query ) ;
 xfree ( query ) ;
 if ( rc != SLURM_SUCCESS ) {
 error ( "Couldn't add cluster root assoc" ) ;
 xfree ( extra ) ;
 added = 0 ;
 break ;
 }
 tmp_extra = slurm_add_slash_to_quotes ( extra + 2 ) ;
 xstrfmtcat ( query , "insert into %s " "(timestamp, action, name, actor, info) " "values (%ld, %u, '%s', '%s', '%s');
" , txn_table , now , DBD_ADD_CLUSTERS , object -> name , user_name , tmp_extra ) ;
 xfree ( tmp_extra ) ;
 xfree ( extra ) ;
 debug4 ( "%d(%s:%d) query\n%s" , mysql_conn -> conn , THIS_FILE , __LINE__ , query ) ;
 rc = mysql_db_query ( mysql_conn , query ) ;
 xfree ( query ) ;
 if ( rc != SLURM_SUCCESS ) {
 error ( "Couldn't add txn" ) ;
 }
 else {
 ListIterator check_itr ;
 char * tmp_name ;
 added ++ ;
 slurm_mutex_lock ( & as_mysql_cluster_list_lock ) ;
 check_itr = list_iterator_create ( as_mysql_cluster_list ) ;
 while ( ( tmp_name = list_next ( check_itr ) ) ) {
 if ( ! xstrcmp ( tmp_name , object -> name ) ) break ;
 }
 list_iterator_destroy ( check_itr ) ;
 if ( ! tmp_name ) {
 list_append ( as_mysql_cluster_list , xstrdup ( object -> name ) ) ;
 list_sort ( as_mysql_cluster_list , ( ListCmpF ) slurm_sort_char_list_asc ) ;
 }
 else error ( "Cluster %s(%s) appears to already be in " "our cache list, not adding." , tmp_name , object -> name ) ;
 slurm_mutex_unlock ( & as_mysql_cluster_list_lock ) ;
 }
 assoc = xmalloc ( sizeof ( slurmdb_assoc_rec_t ) ) ;
 slurmdb_init_assoc_rec ( assoc , 0 ) ;
 list_append ( assoc_list , assoc ) ;
 assoc -> cluster = xstrdup ( object -> name ) ;
 assoc -> user = xstrdup ( "root" ) ;
 assoc -> acct = xstrdup ( "root" ) ;
 assoc -> is_def = 1 ;
 if ( as_mysql_add_assocs ( mysql_conn , uid , assoc_list ) == SLURM_ERROR ) {
 error ( "Problem adding root user association" ) ;
 rc = SLURM_ERROR ;
 }
 }
 end_it : list_iterator_destroy ( itr ) ;
 xfree ( user_name ) ;
 FREE_NULL_LIST ( assoc_list ) ;
 if ( ! added ) reset_mysql_conn ( mysql_conn ) ;
 else if ( has_feds ) as_mysql_add_feds_to_update_list ( mysql_conn ) ;
 return rc ;
 }