static Buf _build_rc_buf ( int rc , uint16_t rpc_version ) {
 Buf buf = NULL ;
 slurm_msg_t msg ;
 return_code_msg_t data ;
 data . return_code = rc ;
 slurm_msg_t_init ( & msg ) ;
 msg . msg_type = RESPONSE_SLURM_RC ;
 msg . data = & data ;
 buf = init_buf ( 128 ) ;
 pack16 ( msg . msg_type , buf ) ;
 if ( pack_msg ( & msg , buf ) != SLURM_SUCCESS ) FREE_NULL_BUFFER ( buf ) ;
 return buf ;
 }