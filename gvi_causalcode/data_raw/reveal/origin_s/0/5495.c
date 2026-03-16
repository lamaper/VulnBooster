void * xmlHashLookup3 ( xmlHashTablePtr table , const xmlChar * name , const xmlChar * name2 , const xmlChar * name3 ) {
 unsigned long key ;
 xmlHashEntryPtr entry ;
 if ( table == NULL ) return ( NULL ) ;
 if ( name == NULL ) return ( NULL ) ;
 key = xmlHashComputeKey ( table , name , name2 , name3 ) ;
 if ( table -> table [ key ] . valid == 0 ) return ( NULL ) ;
 if ( table -> dict ) {
 for ( entry = & ( table -> table [ key ] ) ;
 entry != NULL ;
 entry = entry -> next ) {
 if ( ( entry -> name == name ) && ( entry -> name2 == name2 ) && ( entry -> name3 == name3 ) ) return ( entry -> payload ) ;
 }
 }
 for ( entry = & ( table -> table [ key ] ) ;
 entry != NULL ;
 entry = entry -> next ) {
 if ( ( xmlStrEqual ( entry -> name , name ) ) && ( xmlStrEqual ( entry -> name2 , name2 ) ) && ( xmlStrEqual ( entry -> name3 , name3 ) ) ) return ( entry -> payload ) ;
 }
 return ( NULL ) ;
 }