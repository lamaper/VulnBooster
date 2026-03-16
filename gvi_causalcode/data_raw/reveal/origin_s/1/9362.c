void xmlHashScanFull3 ( xmlHashTablePtr table , const xmlChar * name , const xmlChar * name2 , const xmlChar * name3 , xmlHashScannerFull f , void * data ) {
 int i ;
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
 if ( ( ( name == NULL ) || ( xmlStrEqual ( name , iter -> name ) ) ) && ( ( name2 == NULL ) || ( xmlStrEqual ( name2 , iter -> name2 ) ) ) && ( ( name3 == NULL ) || ( xmlStrEqual ( name3 , iter -> name3 ) ) ) && ( iter -> payload != NULL ) ) {
 f ( iter -> payload , data , iter -> name , iter -> name2 , iter -> name3 ) ;
 }
 iter = next ;
 }
 }
 }
 }