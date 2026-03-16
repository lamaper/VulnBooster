int xmlHashSize ( xmlHashTablePtr table ) {
 if ( table == NULL ) return ( - 1 ) ;
 return ( table -> nbElems ) ;
 }