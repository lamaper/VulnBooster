static int _pack_job_cancel ( void * x , void * arg ) {
 struct job_record * job_ptr = ( struct job_record * ) x ;
 char job_id_str [ BUFSIZ ] ;
 time_t now = time ( NULL ) ;
 ( void ) jobid2fmt ( job_ptr , job_id_str , sizeof ( job_id_str ) ) ;
 info ( "Cancelling aborted pack job submit: %s" , job_id_str ) ;
 job_ptr -> job_state = JOB_CANCELLED ;
 job_ptr -> start_time = now ;
 job_ptr -> end_time = now ;
 job_ptr -> exit_code = 1 ;
 job_completion_logger ( job_ptr , false ) ;
 fed_mgr_job_complete ( job_ptr , 0 , now ) ;
 return 0 ;
 }