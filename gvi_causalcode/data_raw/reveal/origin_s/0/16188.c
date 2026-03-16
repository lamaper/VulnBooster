xmlHashTablePtr xmlHashCreateDict ( int size , xmlDictPtr dict ) {
 xmlHashTablePtr table ;
 table = xmlHashCreate ( size ) ;
 if ( table != NULL ) {
 table -> dict = dict ;
 xmlDictReference ( dict ) ;
 }
 return ( table ) ;
 }