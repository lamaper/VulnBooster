inline static void _slurm_rpc_trigger_set ( slurm_msg_t * msg ) {
 int rc ;
 uid_t uid = g_slurm_auth_get_uid ( msg -> auth_cred , slurmctld_config . auth_info ) ;
 gid_t gid = g_slurm_auth_get_gid ( msg -> auth_cred , slurmctld_config . auth_info ) ;
 trigger_info_msg_t * trigger_ptr = ( trigger_info_msg_t * ) msg -> data ;
 DEF_TIMERS ;
 START_TIMER ;
 debug ( "Processing RPC: REQUEST_TRIGGER_SET from uid=%d" , uid ) ;
 rc = trigger_set ( uid , gid , trigger_ptr ) ;
 END_TIMER2 ( "_slurm_rpc_trigger_set" ) ;
 slurm_send_rc_msg ( msg , rc ) ;
 }