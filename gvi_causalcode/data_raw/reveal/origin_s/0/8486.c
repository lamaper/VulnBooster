extern List as_mysql_modify_clusters ( mysql_conn_t * mysql_conn , uint32_t uid , slurmdb_cluster_cond_t * cluster_cond , slurmdb_cluster_rec_t * cluster ) {
 List ret_list = NULL ;
 int rc = SLURM_SUCCESS ;
 char * object = NULL ;
 char * vals = NULL , * extra = NULL , * query = NULL , * name_char = NULL ;
 time_t now = time ( NULL ) ;
 char * user_name = NULL ;
 int set = 0 ;
 MYSQL_RES * result = NULL ;
 MYSQL_ROW row ;
 bool clust_reg = false , fed_update = false ;
 if ( ! cluster_cond || ! cluster ) {
 error ( "we need something to change" ) ;
 return NULL ;
 }
 if ( check_connection ( mysql_conn ) != SLURM_SUCCESS ) return NULL ;
 if ( ! is_user_min_admin_level ( mysql_conn , uid , SLURMDB_ADMIN_SUPER_USER ) ) {
 errno = ESLURM_ACCESS_DENIED ;
 return NULL ;
 }
 cluster_cond -> with_deleted = 0 ;
 _setup_cluster_cond_limits ( cluster_cond , & extra ) ;
 if ( ! mysql_conn -> cluster_name && cluster_cond -> cluster_list && list_count ( cluster_cond -> cluster_list ) ) mysql_conn -> cluster_name = xstrdup ( list_peek ( cluster_cond -> cluster_list ) ) ;
 set = 0 ;
 if ( cluster -> control_host ) {
 xstrfmtcat ( vals , ", control_host='%s'" , cluster -> control_host ) ;
 set ++ ;
 clust_reg = true ;
 }
 if ( cluster -> control_port ) {
 xstrfmtcat ( vals , ", control_port=%u, last_port=%u" , cluster -> control_port , cluster -> control_port ) ;
 set ++ ;
 clust_reg = true ;
 }
 if ( cluster -> rpc_version ) {
 xstrfmtcat ( vals , ", rpc_version=%u" , cluster -> rpc_version ) ;
 set ++ ;
 clust_reg = true ;
 }
 if ( cluster -> dimensions ) {
 xstrfmtcat ( vals , ", dimensions=%u" , cluster -> dimensions ) ;
 clust_reg = true ;
 }
 if ( cluster -> plugin_id_select ) {
 xstrfmtcat ( vals , ", plugin_id_select=%u" , cluster -> plugin_id_select ) ;
 clust_reg = true ;
 }
 if ( cluster -> flags != NO_VAL ) {
 xstrfmtcat ( vals , ", flags=%u" , cluster -> flags ) ;
 clust_reg = true ;
 }
 if ( cluster -> classification ) {
 xstrfmtcat ( vals , ", classification=%u" , cluster -> classification ) ;
 }
 if ( cluster -> fed . name ) {
 xstrfmtcat ( vals , ", federation='%s'" , cluster -> fed . name ) ;
 fed_update = true ;
 }
 if ( cluster -> fed . state != NO_VAL ) {
 xstrfmtcat ( vals , ", fed_state=%u" , cluster -> fed . state ) ;
 fed_update = true ;
 }
 if ( cluster -> fed . weight != NO_VAL ) {
 xstrfmtcat ( vals , ", fed_weight=%d" , cluster -> fed . weight ) ;
 fed_update = true ;
 }
 if ( ! vals ) {
 xfree ( extra ) ;
 errno = SLURM_NO_CHANGE_IN_DATA ;
 error ( "Nothing to change" ) ;
 return NULL ;
 }
 else if ( clust_reg && ( set != 3 ) ) {
 xfree ( vals ) ;
 xfree ( extra ) ;
 errno = EFAULT ;
 error ( "Need control host, port and rpc version " "to register a cluster" ) ;
 return NULL ;
 }
 xstrfmtcat ( query , "select name, control_port, federation from %s%s;
" , cluster_table , extra ) ;
 if ( debug_flags & DEBUG_FLAG_DB_ASSOC ) DB_DEBUG ( mysql_conn -> conn , "query\n%s" , query ) ;
 if ( ! ( result = mysql_db_query_ret ( mysql_conn , query , 0 ) ) ) {
 xfree ( query ) ;
 xfree ( vals ) ;
 error ( "no result given for %s" , extra ) ;
 xfree ( extra ) ;
 return NULL ;
 }
 xfree ( extra ) ;
 ret_list = list_create ( slurm_destroy_char ) ;
 user_name = uid_to_string ( ( uid_t ) uid ) ;
 while ( ( row = mysql_fetch_row ( result ) ) ) {
 char * tmp_vals = xstrdup ( vals ) ;
 object = xstrdup ( row [ 0 ] ) ;
 if ( cluster -> fed . name ) {
 int id = 0 ;
 char * curr_fed = NULL ;
 uint32_t set_state = NO_VAL ;
 if ( cluster -> fed . name [ 0 ] != '\0' ) {
 rc = as_mysql_get_fed_cluster_id ( mysql_conn , object , cluster -> fed . name , - 1 , & id ) ;
 if ( rc ) {
 error ( "failed to get cluster id for " "federation" ) ;
 xfree ( tmp_vals ) ;
 xfree ( object ) ;
 FREE_NULL_LIST ( ret_list ) ;
 mysql_free_result ( result ) ;
 goto end_it ;
 }
 }
 xstrfmtcat ( tmp_vals , ", fed_id=%d" , id ) ;
 curr_fed = xstrdup ( row [ 2 ] ) ;
 if ( cluster -> fed . name [ 0 ] == '\0' ) set_state = CLUSTER_FED_STATE_NA ;
 else if ( cluster -> fed . state != NO_VAL ) {
 }
 else if ( xstrcmp ( curr_fed , cluster -> fed . name ) ) set_state = CLUSTER_FED_STATE_ACTIVE ;
 if ( set_state != NO_VAL ) xstrfmtcat ( tmp_vals , ", fed_state=%u" , set_state ) ;
 xfree ( curr_fed ) ;
 }
 list_append ( ret_list , object ) ;
 xstrfmtcat ( name_char , "name='%s'" , object ) ;
 rc = modify_common ( mysql_conn , DBD_MODIFY_CLUSTERS , now , user_name , cluster_table , name_char , tmp_vals , NULL ) ;
 xfree ( name_char ) ;
 xfree ( tmp_vals ) ;
 if ( rc == SLURM_ERROR ) {
 error ( "Couldn't modify cluster 1" ) ;
 FREE_NULL_LIST ( ret_list ) ;
 mysql_free_result ( result ) ;
 goto end_it ;
 }
 }
 mysql_free_result ( result ) ;
 xfree ( user_name ) ;
 if ( ! list_count ( ret_list ) ) {
 errno = SLURM_NO_CHANGE_IN_DATA ;
 if ( debug_flags & DEBUG_FLAG_DB_ASSOC ) DB_DEBUG ( mysql_conn -> conn , "didn't effect anything\n%s" , query ) ;
 xfree ( name_char ) ;
 xfree ( vals ) ;
 xfree ( query ) ;
 return ret_list ;
 }
 if ( fed_update ) as_mysql_add_feds_to_update_list ( mysql_conn ) ;
 end_it : xfree ( query ) ;
 xfree ( vals ) ;
 xfree ( user_name ) ;
 return ret_list ;
 }