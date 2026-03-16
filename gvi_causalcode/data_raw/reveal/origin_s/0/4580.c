void fakeDebug ( const char * tag , const char * fmt , ... ) {
 static const int LINE_SIZE = 1024 ;
 char buf [ LINE_SIZE ] ;
 va_list ap ;
 va_start ( ap , fmt ) ;
 vsnprintf ( buf , LINE_SIZE , fmt , ap ) ;
 printf ( "Debug (%s): %s\n" , tag , buf ) ;
 va_end ( ap ) ;
 gFakeDebugLog . append ( buf ) ;
 }