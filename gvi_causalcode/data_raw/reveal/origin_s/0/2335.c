inline static void _slurm_rpc_accounting_update_msg ( slurm_msg_t * msg ) {
 static int active_rpc_cnt = 0 ;
 int rc = SLURM_SUCCESS ;
 uid_t uid = g_slurm_auth_get_uid ( msg -> auth_cred , slurmctld_config . auth_info ) ;
 accounting_update_msg_t * update_ptr = ( accounting_update_msg_t * ) msg -> data ;
 DEF_TIMERS ;
 START_TIMER ;
 debug2 ( "Processing RPC: ACCOUNTING_UPDATE_MSG from uid=%d" , uid ) ;
 if ( ! validate_super_user ( uid ) ) {
 error ( "Update Association request from non-super user uid=%d" , uid ) ;
 slurm_send_rc_msg ( msg , EACCES ) ;
 return ;
 }
 slurm_send_rc_msg ( msg , rc ) ;
 _throttle_start ( & active_rpc_cnt ) ;
 if ( update_ptr -> update_list && list_count ( update_ptr -> update_list ) ) {
 slurmdb_update_object_t * object ;
 slurmdb_update_type_t fed_type = SLURMDB_UPDATE_FEDS ;
 if ( ( object = list_find_first ( update_ptr -> update_list , _find_update_object_in_list , & fed_type ) ) ) {

 error ( "%s: cannot set my name to %s %m" , __func__ , "fedmgr" ) ;
 }

 }
 rc = assoc_mgr_update ( update_ptr -> update_list , 0 ) ;
 }
 _throttle_fini ( & active_rpc_cnt ) ;
 END_TIMER2 ( "_slurm_rpc_accounting_update_msg" ) ;
 if ( rc != SLURM_SUCCESS ) error ( "assoc_mgr_update gave error: %s" , slurm_strerror ( rc ) ) ;
 }