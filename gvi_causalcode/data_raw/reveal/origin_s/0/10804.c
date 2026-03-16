static void _slurm_rpc_sib_msg ( uint32_t uid , slurm_msg_t * msg ) {
 if ( ! msg -> conn ) {
 error ( "Security violation, SIB_SUBMISSION RPC from uid=%d" , uid ) ;
 slurm_send_rc_msg ( msg , ESLURM_ACCESS_DENIED ) ;
 return ;
 }
 fed_mgr_q_sib_msg ( msg , uid ) ;
 }