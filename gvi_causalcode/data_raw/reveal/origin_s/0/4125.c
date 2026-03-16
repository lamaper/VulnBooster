static void _pack_alloc_list_del ( void * x ) {
 resource_allocation_response_msg_t * job_info_resp_msg ;
 job_info_resp_msg = ( resource_allocation_response_msg_t * ) x ;
 job_info_resp_msg -> working_cluster_rec = NULL ;
 slurm_free_resource_allocation_response_msg_members ( job_info_resp_msg ) ;
 xfree ( job_info_resp_msg ) ;
 }