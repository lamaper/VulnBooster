xmlOutputBufferCreateFilenameFunc xmlThrDefOutputBufferCreateFilenameDefault ( xmlOutputBufferCreateFilenameFunc func ) {
 xmlOutputBufferCreateFilenameFunc old ;
 xmlMutexLock ( xmlThrDefMutex ) ;
 old = xmlOutputBufferCreateFilenameValueThrDef ;

 old = __xmlOutputBufferCreateFilename ;
 }

 xmlMutexUnlock ( xmlThrDefMutex ) ;
 return ( old ) ;
 }