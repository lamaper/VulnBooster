void WriteDataChunks ( ArchiveHandle * AH , ParallelState * pstate ) {
 TocEntry * te ;
 for ( te = AH -> toc -> next ;
 te != AH -> toc ;
 te = te -> next ) {
 if ( ! te -> dataDumper ) continue ;
 if ( ( te -> reqs & REQ_DATA ) == 0 ) continue ;
 if ( pstate && pstate -> numWorkers > 1 ) {
 EnsureIdleWorker ( AH , pstate ) ;
 DispatchJobForTocEntry ( AH , pstate , te , ACT_DUMP ) ;
 }
 else WriteDataChunksForTocEntry ( AH , te ) ;
 }
 EnsureWorkersFinished ( AH , pstate ) ;
 }