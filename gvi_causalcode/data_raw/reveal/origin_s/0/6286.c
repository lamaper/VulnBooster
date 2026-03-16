static int _make_step_cred ( struct step_record * step_ptr , slurm_cred_t * * slurm_cred , uint16_t protocol_version ) {
 slurm_cred_arg_t cred_arg ;
 struct job_record * job_ptr = step_ptr -> job_ptr ;
 job_resources_t * job_resrcs_ptr = job_ptr -> job_resrcs ;
 xassert ( job_resrcs_ptr && job_resrcs_ptr -> cpus ) ;
 memset ( & cred_arg , 0 , sizeof ( slurm_cred_arg_t ) ) ;
 cred_arg . jobid = job_ptr -> job_id ;
 cred_arg . stepid = step_ptr -> step_id ;
 cred_arg . uid = job_ptr -> user_id ;
 cred_arg . gid = job_ptr -> group_id ;
 if ( slurmctld_config . send_groups_in_cred ) {
 if ( ! job_ptr -> user_name ) job_ptr -> user_name = uid_to_string_or_null ( job_ptr -> user_id ) ;
 cred_arg . user_name = job_ptr -> user_name ;
 if ( ! job_ptr -> ngids || ! job_ptr -> gids ) job_ptr -> ngids = group_cache_lookup ( job_ptr -> user_id , job_ptr -> group_id , job_ptr -> user_name , & job_ptr -> gids ) ;
 cred_arg . ngids = job_ptr -> ngids ;
 cred_arg . gids = job_ptr -> gids ;
 }
 cred_arg . x11 = job_ptr -> details -> x11 ;
 cred_arg . job_constraints = job_ptr -> details -> features ;
 cred_arg . job_core_bitmap = job_resrcs_ptr -> core_bitmap ;
 cred_arg . job_core_spec = job_ptr -> details -> core_spec ;
 cred_arg . job_hostlist = job_resrcs_ptr -> nodes ;
 cred_arg . job_mem_limit = job_ptr -> details -> pn_min_memory ;
 cred_arg . job_nhosts = job_resrcs_ptr -> nhosts ;
 cred_arg . job_gres_list = job_ptr -> gres_list ;
 cred_arg . step_gres_list = step_ptr -> gres_list ;
 cred_arg . step_core_bitmap = step_ptr -> core_bitmap_job ;

 cred_arg . step_hostlist = job_ptr -> batch_host ;


 cred_arg . cores_per_socket = job_resrcs_ptr -> cores_per_socket ;
 cred_arg . sockets_per_node = job_resrcs_ptr -> sockets_per_node ;
 cred_arg . sock_core_rep_count = job_resrcs_ptr -> sock_core_rep_count ;
 * slurm_cred = slurm_cred_create ( slurmctld_config . cred_ctx , & cred_arg , protocol_version ) ;
 if ( * slurm_cred == NULL ) {
 error ( "slurm_cred_create error" ) ;
 return ESLURM_INVALID_JOB_CREDENTIAL ;
 }
 return SLURM_SUCCESS ;
 }