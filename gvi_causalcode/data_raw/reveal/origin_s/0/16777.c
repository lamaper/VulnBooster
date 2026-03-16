static void _slurm_rpc_update_job ( slurm_msg_t * msg ) {
 int error_code = SLURM_SUCCESS ;
 DEF_TIMERS ;
 job_desc_msg_t * job_desc_msg = ( job_desc_msg_t * ) msg -> data ;
 slurmctld_lock_t fed_read_lock = {
 NO_LOCK , NO_LOCK , NO_LOCK , NO_LOCK , READ_LOCK }
 ;
 slurmctld_lock_t job_write_lock = {
 READ_LOCK , WRITE_LOCK , WRITE_LOCK , READ_LOCK , READ_LOCK }
 ;
 uid_t uid = g_slurm_auth_get_uid ( msg -> auth_cred , slurmctld_config . auth_info ) ;
 lock_slurmctld ( fed_read_lock ) ;
 if ( ! _route_msg_to_origin ( msg , job_desc_msg -> job_id_str , job_desc_msg -> job_id , uid ) ) {
 unlock_slurmctld ( fed_read_lock ) ;
 return ;
 }
 unlock_slurmctld ( fed_read_lock ) ;
 START_TIMER ;
 debug2 ( "Processing RPC: REQUEST_UPDATE_JOB from uid=%d" , uid ) ;
 if ( job_desc_msg -> user_id != NO_VAL ) {
 if ( ! validate_super_user ( uid ) ) {
 error_code = ESLURM_USER_ID_MISSING ;
 error ( "Security violation, REQUEST_UPDATE_JOB RPC from uid=%d" , uid ) ;
 slurm_send_rc_msg ( msg , error_code ) ;
 }
 else {
 uid = job_desc_msg -> user_id ;
 }
 }
 if ( error_code == SLURM_SUCCESS ) {
 int db_inx_max_cnt = 5 , i = 0 ;
 dump_job_desc ( job_desc_msg ) ;
 xstrtolower ( job_desc_msg -> account ) ;
 xstrtolower ( job_desc_msg -> wckey ) ;
 error_code = ESLURM_JOB_SETTING_DB_INX ;
 while ( error_code == ESLURM_JOB_SETTING_DB_INX ) {
 lock_slurmctld ( job_write_lock ) ;
 if ( job_desc_msg -> job_id_str ) error_code = update_job_str ( msg , uid ) ;
 else error_code = update_job ( msg , uid , true ) ;
 unlock_slurmctld ( job_write_lock ) ;
 if ( error_code == ESLURM_JOB_SETTING_DB_INX ) {
 if ( i >= db_inx_max_cnt ) {
 if ( job_desc_msg -> job_id_str ) {
 info ( "%s: can't update job, waited %d seconds for job %s to get a db_index, but it hasn't happened yet. Giving up and informing the user" , __func__ , db_inx_max_cnt , job_desc_msg -> job_id_str ) ;
 }
 else {
 info ( "%s: can't update job, waited %d seconds for job %u to get a db_index, but it hasn't happened yet. Giving up and informing the user" , __func__ , db_inx_max_cnt , job_desc_msg -> job_id ) ;
 }
 slurm_send_rc_msg ( msg , error_code ) ;
 break ;
 }
 i ++ ;
 if ( job_desc_msg -> job_id_str ) {
 debug ( "%s: We cannot update job %s at the moment, we are setting the db index, waiting" , __func__ , job_desc_msg -> job_id_str ) ;
 }
 else {
 debug ( "%s: We cannot update job %u at the moment, we are setting the db index, waiting" , __func__ , job_desc_msg -> job_id ) ;
 }
 sleep ( 1 ) ;
 }
 }
 }
 END_TIMER2 ( "_slurm_rpc_update_job" ) ;
 if ( error_code ) {
 if ( job_desc_msg -> job_id_str ) {
 info ( "%s: JobId=%s uid=%d: %s" , __func__ , job_desc_msg -> job_id_str , uid , slurm_strerror ( error_code ) ) ;
 }
 else {
 info ( "%s: JobId=%u uid=%d: %s" , __func__ , job_desc_msg -> job_id , uid , slurm_strerror ( error_code ) ) ;
 }
 }
 else {
 if ( job_desc_msg -> job_id_str ) {
 info ( "%s: complete JobId=%s uid=%d %s" , __func__ , job_desc_msg -> job_id_str , uid , TIME_STR ) ;
 }
 else {
 info ( "%s: complete JobId=%u uid=%d %s" , __func__ , job_desc_msg -> job_id , uid , TIME_STR ) ;
 }
 schedule_job_save ( ) ;
 schedule_node_save ( ) ;
 queue_job_scheduler ( ) ;
 }
 }