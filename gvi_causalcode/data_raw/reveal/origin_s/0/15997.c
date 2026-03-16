int xmlHashRemoveEntry3 ( xmlHashTablePtr table , const xmlChar * name , const xmlChar * name2 , const xmlChar * name3 , xmlHashDeallocator f ) {
 unsigned long key ;
 xmlHashEntryPtr entry ;
 xmlHashEntryPtr prev = NULL ;
 if ( table == NULL || name == NULL ) return ( - 1 ) ;
 key = xmlHashComputeKey ( table , name , name2 , name3 ) ;
 if ( table -> table [ key ] . valid == 0 ) {
 return ( - 1 ) ;
 }
 else {
 for ( entry = & ( table -> table [ key ] ) ;
 entry != NULL ;
 entry = entry -> next ) {
 if ( xmlStrEqual ( entry -> name , name ) && xmlStrEqual ( entry -> name2 , name2 ) && xmlStrEqual ( entry -> name3 , name3 ) ) {
 if ( ( f != NULL ) && ( entry -> payload != NULL ) ) f ( entry -> payload , entry -> name ) ;
 entry -> payload = NULL ;
 if ( table -> dict == NULL ) {
 if ( entry -> name ) xmlFree ( entry -> name ) ;
 if ( entry -> name2 ) xmlFree ( entry -> name2 ) ;
 if ( entry -> name3 ) xmlFree ( entry -> name3 ) ;
 }
 if ( prev ) {
 prev -> next = entry -> next ;
 xmlFree ( entry ) ;
 }
 else {
 if ( entry -> next == NULL ) {
 entry -> valid = 0 ;
 }
 else {
 entry = entry -> next ;
 memcpy ( & ( table -> table [ key ] ) , entry , sizeof ( xmlHashEntry ) ) ;
 xmlFree ( entry ) ;
 }
 }
 table -> nbElems -- ;
 return ( 0 ) ;
 }
 prev = entry ;
 }
 return ( - 1 ) ;
 }
 }