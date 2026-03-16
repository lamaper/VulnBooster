static int _process_persist_conn ( void * arg , persist_msg_t * persist_msg , Buf * out_buffer , uint32_t * uid ) {
 slurm_msg_t msg ;
 slurm_persist_conn_t * persist_conn = arg ;
 if ( * uid == NO_VAL ) * uid = g_slurm_auth_get_uid ( persist_conn -> auth_cred , slurmctld_config . auth_info ) ;
 * out_buffer = NULL ;
 slurm_msg_t_init ( & msg ) ;
 msg . auth_cred = persist_conn -> auth_cred ;
 msg . conn = persist_conn ;
 msg . conn_fd = persist_conn -> fd ;
 msg . msg_type = persist_msg -> msg_type ;
 msg . data = persist_msg -> data ;
 slurmctld_req ( & msg , NULL ) ;
 return SLURM_SUCCESS ;
 }