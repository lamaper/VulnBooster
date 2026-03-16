static void mark_work_done ( ArchiveHandle * AH , TocEntry * ready_list , int worker , int status , ParallelState * pstate ) {
 TocEntry * te = NULL ;
 te = pstate -> parallelSlot [ worker ] . args -> te ;
 if ( te == NULL ) exit_horribly ( modulename , "could not find slot of finished worker\n" ) ;
 ahlog ( AH , 1 , "finished item %d %s %s\n" , te -> dumpId , te -> desc , te -> tag ) ;
 if ( status == WORKER_CREATE_DONE ) mark_create_done ( AH , te ) ;
 else if ( status == WORKER_INHIBIT_DATA ) {
 inhibit_data_for_failed_table ( AH , te ) ;
 AH -> public . n_errors ++ ;
 }
 else if ( status == WORKER_IGNORED_ERRORS ) AH -> public . n_errors ++ ;
 else if ( status != 0 ) exit_horribly ( modulename , "worker process failed: exit code %d\n" , status ) ;
 reduce_dependencies ( AH , te , ready_list ) ;
 }