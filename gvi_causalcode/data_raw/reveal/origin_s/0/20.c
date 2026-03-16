static void dumpsid ( FILE * cfff , struct alltabs * at , char * str , int oper ) {
 if ( str == NULL ) return ;
 dumpint ( cfff , storesid ( at , str ) ) ;
 dumpoper ( cfff , oper ) ;
 }