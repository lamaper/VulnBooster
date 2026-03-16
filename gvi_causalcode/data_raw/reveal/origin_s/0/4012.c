static void DumpStrArray ( char * pt , FILE * cfff , int oper ) {
 real d , last = 0 ;
 char * end ;
 while ( * pt == ' ' ) ++ pt ;
 if ( * pt == '\0' ) return ;
 if ( * pt == '[' ) ++ pt ;
 while ( * pt == ' ' ) ++ pt ;
 while ( * pt != ']' && * pt != '\0' ) {
 d = strtod ( pt , & end ) ;
 if ( pt == end ) break ;
 dumpdbl ( cfff , d - last ) ;
 last = d ;
 pt = end ;
 while ( * pt == ' ' ) ++ pt ;
 }
 dumpoper ( cfff , oper ) ;
 }