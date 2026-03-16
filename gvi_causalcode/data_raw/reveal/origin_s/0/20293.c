static int _route_msg_to_origin ( slurm_msg_t * msg , char * src_job_id_str , uint32_t src_job_id , uid_t uid ) {
 xassert ( msg ) ;
 if ( ! msg -> conn && fed_mgr_fed_rec ) {
 uint32_t job_id , origin_id ;
 if ( src_job_id_str ) job_id = strtol ( src_job_id_str , NULL , 10 ) ;
 else job_id = src_job_id ;
 origin_id = fed_mgr_get_cluster_id ( job_id ) ;
 if ( origin_id && ( origin_id != fed_mgr_cluster_rec -> fed . id ) ) {
 slurmdb_cluster_rec_t * dst = fed_mgr_get_cluster_by_id ( origin_id ) ;
 if ( ! dst ) {
 error ( "couldn't find cluster by cluster id %d" , origin_id ) ;
 slurm_send_rc_msg ( msg , SLURM_ERROR ) ;
 }
 else {
 slurm_send_reroute_msg ( msg , dst ) ;
 info ( "%s: %s job %d uid %d routed to %s" , __func__ , rpc_num2string ( msg -> msg_type ) , job_id , uid , dst -> name ) ;
 }
 return SLURM_SUCCESS ;
 }
 }
 return SLURM_ERROR ;
 }