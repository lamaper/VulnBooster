static void DumpStrDouble ( char * pt , FILE * cfff , int oper ) {
 real d ;
 if ( * pt == '[' ) ++ pt ;
 d = strtod ( pt , NULL ) ;
 dumpdbloper ( cfff , d , oper ) ;
 }