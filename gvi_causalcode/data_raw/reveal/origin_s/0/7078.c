inline static void _slurm_rpc_accounting_first_reg ( slurm_msg_t * msg ) {
 uid_t uid = g_slurm_auth_get_uid ( msg -> auth_cred , slurmctld_config . auth_info ) ;
 time_t event_time = time ( NULL ) ;
 DEF_TIMERS ;
 START_TIMER ;
 debug2 ( "Processing RPC: ACCOUNTING_FIRST_REG from uid=%d" , uid ) ;
 if ( ! validate_super_user ( uid ) ) {
 error ( "First Registration request from non-super user uid=%d" , uid ) ;
 return ;
 }
 send_all_to_accounting ( event_time , ACCOUNTING_FIRST_REG ) ;
 END_TIMER2 ( "_slurm_rpc_accounting_first_reg" ) ;
 }