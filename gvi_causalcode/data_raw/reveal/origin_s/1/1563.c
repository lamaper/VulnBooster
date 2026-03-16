xmlHashTablePtr xmlHashCopy ( xmlHashTablePtr table , xmlHashCopier f ) {
 int i ;
 xmlHashEntryPtr iter ;
 xmlHashEntryPtr next ;
 xmlHashTablePtr ret ;
 if ( table == NULL ) return ( NULL ) ;
 if ( f == NULL ) return ( NULL ) ;
 ret = xmlHashCreate ( table -> size ) ;
 if ( table -> table ) {
 for ( i = 0 ;
 i < table -> size ;
 i ++ ) {
 if ( table -> table [ i ] . valid == 0 ) continue ;
 iter = & ( table -> table [ i ] ) ;
 while ( iter ) {
 next = iter -> next ;
 xmlHashAddEntry3 ( ret , iter -> name , iter -> name2 , iter -> name3 , f ( iter -> payload , iter -> name ) ) ;
 iter = next ;
 }
 }
 }
 ret -> nbElems = table -> nbElems ;
 return ( ret ) ;
 }