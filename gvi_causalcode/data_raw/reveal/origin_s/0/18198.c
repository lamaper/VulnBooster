inline static void _slurm_rpc_set_fs_dampening_factor ( slurm_msg_t * msg ) {
 uid_t uid = g_slurm_auth_get_uid ( msg -> auth_cred , slurmctld_config . auth_info ) ;
 slurmctld_lock_t config_write_lock = {
 WRITE_LOCK , WRITE_LOCK , READ_LOCK , READ_LOCK , READ_LOCK }
 ;
 set_fs_dampening_factor_msg_t * request_msg = ( set_fs_dampening_factor_msg_t * ) msg -> data ;
 uint16_t factor ;
 debug2 ( "Processing RPC: REQUEST_SET_FS_DAMPENING_FACTOR from uid=%d" , uid ) ;
 if ( ! validate_super_user ( uid ) ) {
 error ( "set FairShareDampeningFactor request from non-super user uid=%d" , uid ) ;
 slurm_send_rc_msg ( msg , EACCES ) ;
 return ;
 }
 factor = request_msg -> dampening_factor ;
 lock_slurmctld ( config_write_lock ) ;
 slurm_set_fs_dampening_factor ( factor ) ;
 slurmctld_conf . last_update = time ( NULL ) ;
 priority_g_reconfig ( false ) ;
 unlock_slurmctld ( config_write_lock ) ;
 info ( "Set FairShareDampeningFactor to %u" , factor ) ;
 slurm_send_rc_msg ( msg , SLURM_SUCCESS ) ;
 }