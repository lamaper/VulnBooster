int parallel_restore ( ParallelArgs * args ) {
 ArchiveHandle * AH = args -> AH ;
 TocEntry * te = args -> te ;
 int status ;
 Assert ( AH -> connection != NULL ) ;
 AH -> public . n_errors = 0 ;
 status = restore_toc_entry ( AH , te , true ) ;
 return status ;
 }