NewConverter * CnvExtOpen ( UCMFile * ucm ) {
 CnvExtData * extData ;
 extData = ( CnvExtData * ) uprv_malloc ( sizeof ( CnvExtData ) ) ;
 if ( extData == NULL ) {
 printf ( "out of memory\n" ) ;
 exit ( U_MEMORY_ALLOCATION_ERROR ) ;
 }
 uprv_memset ( extData , 0 , sizeof ( CnvExtData ) ) ;
 extData -> ucm = ucm ;
 extData -> newConverter . close = CnvExtClose ;
 extData -> newConverter . isValid = CnvExtIsValid ;
 extData -> newConverter . addTable = CnvExtAddTable ;
 extData -> newConverter . write = CnvExtWrite ;
 return & extData -> newConverter ;
 }