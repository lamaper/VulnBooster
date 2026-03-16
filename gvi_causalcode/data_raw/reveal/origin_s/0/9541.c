extern int as_mysql_register_ctld ( mysql_conn_t * mysql_conn , char * cluster , uint16_t port ) {
 char * query = NULL ;
 char * address = NULL ;
 char hostname [ 255 ] ;
 time_t now = time ( NULL ) ;
 uint32_t flags = slurmdb_setup_cluster_flags ( ) ;
 int rc = SLURM_SUCCESS ;
 if ( slurmdbd_conf ) fatal ( "clusteracct_storage_g_register_ctld " "should never be called from the slurmdbd." ) ;
 if ( check_connection ( mysql_conn ) != SLURM_SUCCESS ) return ESLURM_DB_CONNECTION ;
 if ( ! mysql_conn -> cluster_name ) {
 error ( "%s:%d no cluster name" , THIS_FILE , __LINE__ ) ;
 return SLURM_ERROR ;
 }
 if ( ! mysql_conn -> cluster_name ) mysql_conn -> cluster_name = xstrdup ( cluster ) ;
 info ( "Registering slurmctld for cluster %s at port %u in database." , cluster , port ) ;
 gethostname ( hostname , sizeof ( hostname ) ) ;
 if ( slurmctld_conf . backup_controller && ! xstrcmp ( slurmctld_conf . backup_controller , hostname ) ) {
 address = slurmctld_conf . backup_addr ;
 }
 else address = slurmctld_conf . control_addr ;
 query = xstrdup_printf ( "update %s set deleted=0, mod_time=%ld, " "control_host='%s', control_port=%u, last_port=%u, " "rpc_version=%d, dimensions=%d, flags=%u, " "plugin_id_select=%d where name='%s';
" , cluster_table , now , address , port , port , SLURM_PROTOCOL_VERSION , SYSTEM_DIMENSIONS , flags , select_get_plugin_id ( ) , cluster ) ;
 xstrfmtcat ( query , "insert into %s " "(timestamp, action, name, actor, info) " "values (%ld, %d, '%s', '%s', '%s %u %u %u %u');
" , txn_table , now , DBD_MODIFY_CLUSTERS , cluster , slurmctld_conf . slurm_user_name , address , port , SYSTEM_DIMENSIONS , flags , select_get_plugin_id ( ) ) ;
 if ( debug_flags & DEBUG_FLAG_DB_ASSOC ) DB_DEBUG ( mysql_conn -> conn , "query\n%s" , query ) ;
 rc = mysql_db_query ( mysql_conn , query ) ;
 xfree ( query ) ;
 return rc ;
 }