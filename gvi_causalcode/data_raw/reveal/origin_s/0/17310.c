inline static void _slurm_rpc_accounting_register_ctld ( slurm_msg_t * msg ) {
 uid_t uid = g_slurm_auth_get_uid ( msg -> auth_cred , slurmctld_config . auth_info ) ;
 DEF_TIMERS ;
 START_TIMER ;
 debug2 ( "Processing RPC: ACCOUNTING_REGISTER_CTLD from uid=%d" , uid ) ;
 if ( ! validate_super_user ( uid ) ) {
 error ( "Registration request from non-super user uid=%d" , uid ) ;
 return ;
 }
 clusteracct_storage_g_register_ctld ( acct_db_conn , slurmctld_conf . slurmctld_port ) ;
 END_TIMER2 ( "_slurm_rpc_accounting_register_ctld" ) ;
 }