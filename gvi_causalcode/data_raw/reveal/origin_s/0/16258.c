static void _slurm_rpc_sib_job_lock ( uint32_t uid , slurm_msg_t * msg ) {
 int rc ;
 sib_msg_t * sib_msg = msg -> data ;
 if ( ! msg -> conn ) {
 error ( "Security violation, SIB_JOB_LOCK RPC from uid=%d" , uid ) ;
 slurm_send_rc_msg ( msg , ESLURM_ACCESS_DENIED ) ;
 return ;
 }
 rc = fed_mgr_job_lock_set ( sib_msg -> job_id , sib_msg -> cluster_id ) ;
 slurm_send_rc_msg ( msg , rc ) ;
 }