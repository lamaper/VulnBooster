void xmlHashFree ( xmlHashTablePtr table , xmlHashDeallocator f ) {
 int i ;
 xmlHashEntryPtr iter ;
 xmlHashEntryPtr next ;
 int inside_table = 0 ;
 int nbElems ;
 if ( table == NULL ) return ;
 if ( table -> table ) {
 nbElems = table -> nbElems ;
 for ( i = 0 ;
 ( i < table -> size ) && ( nbElems > 0 ) ;
 i ++ ) {
 iter = & ( table -> table [ i ] ) ;
 if ( iter -> valid == 0 ) continue ;
 inside_table = 1 ;
 while ( iter ) {
 next = iter -> next ;
 if ( ( f != NULL ) && ( iter -> payload != NULL ) ) f ( iter -> payload , iter -> name ) ;
 if ( table -> dict == NULL ) {
 if ( iter -> name ) xmlFree ( iter -> name ) ;
 if ( iter -> name2 ) xmlFree ( iter -> name2 ) ;
 if ( iter -> name3 ) xmlFree ( iter -> name3 ) ;
 }
 iter -> payload = NULL ;
 if ( ! inside_table ) xmlFree ( iter ) ;
 nbElems -- ;
 inside_table = 0 ;
 iter = next ;
 }
 }
 xmlFree ( table -> table ) ;
 }
 if ( table -> dict ) xmlDictFree ( table -> dict ) ;
 xmlFree ( table ) ;
 }