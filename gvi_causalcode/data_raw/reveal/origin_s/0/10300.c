static const char * ultag_getExtlang ( const ULanguageTag * langtag , int32_t idx ) {
 if ( idx >= 0 && idx < MAXEXTLANG ) {
 return langtag -> extlang [ idx ] ;
 }
 return NULL ;
 }