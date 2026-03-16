static void virLogCloseFd ( void * data ) {
 int fd = ( intptr_t ) data ;
 VIR_LOG_CLOSE ( fd ) ;
 }