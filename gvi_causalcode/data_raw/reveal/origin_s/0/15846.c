static int32_t ultag_getExtlangSize ( const ULanguageTag * langtag ) {
 int32_t size = 0 ;
 int32_t i ;
 for ( i = 0 ;
 i < MAXEXTLANG ;
 i ++ ) {
 if ( langtag -> extlang [ i ] ) {
 size ++ ;
 }
 }
 return size ;
 }