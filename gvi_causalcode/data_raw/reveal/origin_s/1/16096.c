void xmlHashScanFull ( xmlHashTablePtr table , xmlHashScannerFull f , void * data ) {
 int i , nb ;
 xmlHashEntryPtr iter ;
 xmlHashEntryPtr next ;
 if ( table == NULL ) return ;
 if ( f == NULL ) return ;
 if ( table -> table ) {
 for ( i = 0 ;
 i < table -> size ;
 i ++ ) {
 if ( table -> table [ i ] . valid == 0 ) continue ;
 iter = & ( table -> table [ i ] ) ;
 while ( iter ) {
 next = iter -> next ;
 nb = table -> nbElems ;
 if ( ( f != NULL ) && ( iter -> payload != NULL ) ) f ( iter -> payload , data , iter -> name , iter -> name2 , iter -> name3 ) ;
 if ( nb != table -> nbElems ) {
 if ( iter == & ( table -> table [ i ] ) ) {
 if ( table -> table [ i ] . valid == 0 ) iter = NULL ;
 if ( table -> table [ i ] . next != next ) iter = & ( table -> table [ i ] ) ;
 }
 else iter = next ;
 }
 else iter = next ;
 }
 }
 }
 }