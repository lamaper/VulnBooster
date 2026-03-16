static void restore_toc_entries_parallel ( ArchiveHandle * AH , ParallelState * pstate , TocEntry * pending_list ) {
 int work_status ;
 bool skipped_some ;
 TocEntry ready_list ;
 TocEntry * next_work_item ;
 int ret_child ;
 ahlog ( AH , 2 , "entering restore_toc_entries_parallel\n" ) ;
 par_list_header_init ( & ready_list ) ;
 skipped_some = false ;
 for ( next_work_item = AH -> toc -> next ;
 next_work_item != AH -> toc ;
 next_work_item = next_work_item -> next ) {
 if ( next_work_item -> section == SECTION_PRE_DATA ) {
 continue ;
 }
 if ( next_work_item -> section == SECTION_DATA || next_work_item -> section == SECTION_POST_DATA ) {
 skipped_some = true ;
 }
 else {
 if ( ! skipped_some ) continue ;
 }
 if ( next_work_item -> depCount > 0 ) par_list_append ( pending_list , next_work_item ) ;
 else par_list_append ( & ready_list , next_work_item ) ;
 }
 ahlog ( AH , 1 , "entering main parallel loop\n" ) ;
 while ( ( next_work_item = get_next_work_item ( AH , & ready_list , pstate ) ) != NULL || ! IsEveryWorkerIdle ( pstate ) ) {
 if ( next_work_item != NULL ) {
 if ( ( next_work_item -> reqs & ( REQ_SCHEMA | REQ_DATA ) ) == 0 || _tocEntryIsACL ( next_work_item ) ) {
 ahlog ( AH , 1 , "skipping item %d %s %s\n" , next_work_item -> dumpId , next_work_item -> desc , next_work_item -> tag ) ;
 par_list_remove ( next_work_item ) ;
 reduce_dependencies ( AH , next_work_item , & ready_list ) ;
 continue ;
 }
 ahlog ( AH , 1 , "launching item %d %s %s\n" , next_work_item -> dumpId , next_work_item -> desc , next_work_item -> tag ) ;
 par_list_remove ( next_work_item ) ;
 DispatchJobForTocEntry ( AH , pstate , next_work_item , ACT_RESTORE ) ;
 }
 else {
 }
 for ( ;
 ;
 ) {
 int nTerm = 0 ;
 ListenToWorkers ( AH , pstate , ! next_work_item ) ;
 while ( ( ret_child = ReapWorkerStatus ( pstate , & work_status ) ) != NO_SLOT ) {
 nTerm ++ ;
 mark_work_done ( AH , & ready_list , ret_child , work_status , pstate ) ;
 }
 if ( nTerm > 0 ) break ;
 if ( GetIdleWorker ( pstate ) != NO_SLOT ) break ;
 ListenToWorkers ( AH , pstate , true ) ;
 }
 }
 ahlog ( AH , 1 , "finished main parallel loop\n" ) ;
 }