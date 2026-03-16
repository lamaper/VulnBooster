void virLogUnlock ( void ) {
 virMutexUnlock ( & virLogMutex ) ;
 }