Archive * CreateArchive ( const char * FileSpec , const ArchiveFormat fmt , const int compression , ArchiveMode mode , SetupWorkerPtr setupDumpWorker ) {
 ArchiveHandle * AH = _allocAH ( FileSpec , fmt , compression , mode , setupDumpWorker ) ;
 return ( Archive * ) AH ;
 }