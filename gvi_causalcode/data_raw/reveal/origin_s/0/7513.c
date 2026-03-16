inline static void _slurm_rpc_trigger_pull ( slurm_msg_t * msg ) {
 int rc ;
 uid_t uid = g_slurm_auth_get_uid ( msg -> auth_cred , slurmctld_config . auth_info ) ;
 trigger_info_msg_t * trigger_ptr = ( trigger_info_msg_t * ) msg -> data ;
 DEF_TIMERS ;
 START_TIMER ;
 debug ( "Processing RPC: REQUEST_TRIGGER_PULL from uid=%u" , ( unsigned int ) uid ) ;
 if ( ! validate_slurm_user ( uid ) ) {
 rc = ESLURM_USER_ID_MISSING ;
 error ( "Security violation, REQUEST_TRIGGER_PULL RPC " "from uid=%d" , uid ) ;
 }
 else rc = trigger_pull ( trigger_ptr ) ;
 END_TIMER2 ( "_slurm_rpc_trigger_pull" ) ;
 slurm_send_rc_msg ( msg , rc ) ;
 }