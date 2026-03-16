static void _del_alloc_pack_msg ( void * x ) {
 resource_allocation_response_msg_t * alloc_msg ;
 alloc_msg = ( resource_allocation_response_msg_t * ) x ;
 alloc_msg -> working_cluster_rec = NULL ;
 slurm_free_resource_allocation_response_msg_members ( alloc_msg ) ;
 xfree ( alloc_msg ) ;
 }