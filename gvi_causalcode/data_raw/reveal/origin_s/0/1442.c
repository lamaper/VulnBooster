Archive * OpenArchive ( const char * FileSpec , const ArchiveFormat fmt ) {
 ArchiveHandle * AH = _allocAH ( FileSpec , fmt , 0 , archModeRead , setupRestoreWorker ) ;
 return ( Archive * ) AH ;
 }