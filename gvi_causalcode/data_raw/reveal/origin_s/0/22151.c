static void _slurm_rpc_job_sbcast_cred ( slurm_msg_t * msg ) {


 slurm_msg_t response_msg ;
 struct job_record * job_ptr = NULL , * job_pack_ptr ;
 struct step_record * step_ptr ;
 char * local_node_list = NULL , * node_list = NULL ;
 struct node_record * node_ptr ;
 slurm_addr_t * node_addr = NULL ;
 hostlist_t host_list = NULL ;
 char * this_node_name ;
 int node_inx = 0 ;
 uint32_t node_cnt = 0 ;
 DEF_TIMERS ;
 step_alloc_info_msg_t * job_info_msg = ( step_alloc_info_msg_t * ) msg -> data ;
 job_sbcast_cred_msg_t job_info_resp_msg ;
 sbcast_cred_arg_t sbcast_arg ;
 sbcast_cred_t * sbcast_cred ;
 slurmctld_lock_t job_read_lock = {
 READ_LOCK , READ_LOCK , READ_LOCK , NO_LOCK , NO_LOCK }
 ;
 uid_t uid = g_slurm_auth_get_uid ( msg -> auth_cred , slurmctld_config . auth_info ) ;
 START_TIMER ;
 debug2 ( "Processing RPC: REQUEST_JOB_SBCAST_CRED from uid=%d" , uid ) ;
 lock_slurmctld ( job_read_lock ) ;
 if ( job_info_msg -> pack_job_offset == NO_VAL ) {
 bitstr_t * node_bitmap = NULL ;
 ListIterator iter ;
 error_code = job_alloc_info ( uid , job_info_msg -> job_id , & job_ptr ) ;
 if ( job_ptr && job_ptr -> pack_job_list ) {
 job_info_msg -> step_id = NO_VAL ;
 iter = list_iterator_create ( job_ptr -> pack_job_list ) ;
 while ( ( job_pack_ptr = ( struct job_record * ) list_next ( iter ) ) ) {
 error_code = job_alloc_info_ptr ( uid , job_pack_ptr ) ;
 if ( error_code ) break ;
 if ( ! job_pack_ptr -> node_bitmap ) {
 debug ( "%s: Job %u lacks node bitmap" , __func__ , job_pack_ptr -> job_id ) ;
 }
 else if ( ! node_bitmap ) {
 node_bitmap = bit_copy ( job_pack_ptr -> node_bitmap ) ;
 }
 else {
 bit_or ( node_bitmap , job_pack_ptr -> node_bitmap ) ;
 }
 }
 list_iterator_destroy ( iter ) ;
 if ( ! error_code ) {
 node_cnt = bit_set_count ( node_bitmap ) ;
 local_node_list = bitmap2node_name ( node_bitmap ) ;
 node_list = local_node_list ;
 node_addr = _build_node_addr ( node_list , node_cnt , job_ptr -> job_id ) ;
 if ( ! node_addr ) error_code = SLURM_ERROR ;
 }
 FREE_NULL_BITMAP ( node_bitmap ) ;
 }
 }
 else {
 job_ptr = find_job_pack_record ( job_info_msg -> job_id , job_info_msg -> pack_job_offset ) ;
 if ( job_ptr ) {
 job_info_msg -> job_id = job_ptr -> job_id ;
 error_code = job_alloc_info ( uid , job_info_msg -> job_id , & job_ptr ) ;
 }
 else {
 error_code = ESLURM_INVALID_JOB_ID ;
 }
 }
 if ( job_ptr && ! validate_operator ( uid ) && job_ptr -> user_id != uid ) error_code = ESLURM_USER_ID_MISSING ;
 if ( ( error_code == SLURM_SUCCESS ) && job_ptr && ( job_info_msg -> step_id != NO_VAL ) ) {
 step_ptr = find_step_record ( job_ptr , job_info_msg -> step_id ) ;
 if ( ! step_ptr ) {
 job_ptr = NULL ;
 error_code = ESLURM_INVALID_JOB_ID ;
 }
 else if ( step_ptr -> step_layout && ( step_ptr -> step_layout -> node_cnt != job_ptr -> node_cnt ) ) {
 node_cnt = step_ptr -> step_layout -> node_cnt ;
 node_list = step_ptr -> step_layout -> node_list ;
 if ( ( host_list = hostlist_create ( node_list ) ) == NULL ) {
 fatal ( "hostlist_create error for %s: %m" , node_list ) ;
 return ;
 }
 node_addr = xmalloc ( sizeof ( slurm_addr_t ) * node_cnt ) ;
 while ( ( this_node_name = hostlist_shift ( host_list ) ) ) {
 if ( ( node_ptr = find_node_record ( this_node_name ) ) ) {
 memcpy ( & node_addr [ node_inx ++ ] , & node_ptr -> slurm_addr , sizeof ( slurm_addr_t ) ) ;
 }
 else {
 error ( "Invalid node %s in Step=%u.%u" , this_node_name , job_ptr -> job_id , step_ptr -> step_id ) ;
 }
 free ( this_node_name ) ;
 }
 hostlist_destroy ( host_list ) ;
 }
 }
 if ( ( error_code == SLURM_SUCCESS ) && job_ptr && ! node_addr ) {
 node_addr = job_ptr -> node_addr ;
 node_cnt = job_ptr -> node_cnt ;
 node_list = job_ptr -> nodes ;
 node_addr = xmalloc ( sizeof ( slurm_addr_t ) * node_cnt ) ;
 memcpy ( node_addr , job_ptr -> node_addr , ( sizeof ( slurm_addr_t ) * node_cnt ) ) ;
 }
 END_TIMER2 ( "_slurm_rpc_job_sbcast_cred" ) ;
 if ( error_code || ( job_ptr == NULL ) ) {
 unlock_slurmctld ( job_read_lock ) ;
 debug2 ( "_slurm_rpc_job_sbcast_cred: JobId=%u, uid=%u: %s" , job_info_msg -> job_id , uid , slurm_strerror ( error_code ) ) ;
 slurm_send_rc_msg ( msg , error_code ) ;
 xfree ( local_node_list ) ;
 xfree ( node_addr ) ;
 return ;
 }
 memset ( & sbcast_arg , 0 , sizeof ( sbcast_cred_arg_t ) ) ;
 sbcast_arg . job_id = job_ptr -> job_id ;
 sbcast_arg . uid = job_ptr -> user_id ;
 sbcast_arg . gid = job_ptr -> group_id ;
 if ( slurmctld_config . send_groups_in_cred ) {
 if ( ! job_ptr -> user_name ) job_ptr -> user_name = uid_to_string_or_null ( job_ptr -> user_id ) ;
 sbcast_arg . user_name = job_ptr -> user_name ;
 if ( ! job_ptr -> ngids || ! job_ptr -> gids ) job_ptr -> ngids = group_cache_lookup ( job_ptr -> user_id , job_ptr -> group_id , job_ptr -> user_name , & job_ptr -> gids ) ;
 sbcast_arg . ngids = job_ptr -> ngids ;
 sbcast_arg . gids = job_ptr -> gids ;
 }
 sbcast_arg . nodes = node_list ;
 sbcast_arg . expiration = job_ptr -> end_time ;
 if ( ( sbcast_cred = create_sbcast_cred ( slurmctld_config . cred_ctx , & sbcast_arg , msg -> protocol_version ) ) == NULL ) {
 unlock_slurmctld ( job_read_lock ) ;
 error ( "_slurm_rpc_job_sbcast_cred JobId=%u cred create error" , job_info_msg -> job_id ) ;
 slurm_send_rc_msg ( msg , SLURM_ERROR ) ;
 }
 else {
 if ( job_ptr && ( job_info_msg -> step_id != NO_VAL ) ) {
 info ( "_slurm_rpc_job_sbcast_cred Job=%u NodeList=%s %s" , job_info_msg -> job_id , node_list , TIME_STR ) ;
 }
 else {
 info ( "_slurm_rpc_job_sbcast_cred Step=%u.%u " "NodeList=%s %s" , job_info_msg -> job_id , job_info_msg -> step_id , node_list , TIME_STR ) ;
 }
 job_info_resp_msg . job_id = job_ptr -> job_id ;
 job_info_resp_msg . node_addr = node_addr ;
 job_info_resp_msg . node_cnt = node_cnt ;
 job_info_resp_msg . node_list = xstrdup ( node_list ) ;
 job_info_resp_msg . sbcast_cred = sbcast_cred ;
 unlock_slurmctld ( job_read_lock ) ;
 slurm_msg_t_init ( & response_msg ) ;
 response_msg . flags = msg -> flags ;
 response_msg . protocol_version = msg -> protocol_version ;
 response_msg . msg_type = RESPONSE_JOB_SBCAST_CRED ;
 response_msg . data = & job_info_resp_msg ;
 slurm_send_node_msg ( msg -> conn_fd , & response_msg ) ;
 xfree ( job_info_resp_msg . node_list ) ;
 delete_sbcast_cred ( sbcast_cred ) ;
 }
 xfree ( local_node_list ) ;
 xfree ( node_addr ) ;
