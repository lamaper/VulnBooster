void * xmlHashQLookup3 ( xmlHashTablePtr table , const xmlChar * prefix , const xmlChar * name , const xmlChar * prefix2 , const xmlChar * name2 , const xmlChar * prefix3 , const xmlChar * name3 ) {
 unsigned long key ;
 xmlHashEntryPtr entry ;
 if ( table == NULL ) return ( NULL ) ;
 if ( name == NULL ) return ( NULL ) ;
 key = xmlHashComputeQKey ( table , prefix , name , prefix2 , name2 , prefix3 , name3 ) ;
 if ( table -> table [ key ] . valid == 0 ) return ( NULL ) ;
 for ( entry = & ( table -> table [ key ] ) ;
 entry != NULL ;
 entry = entry -> next ) {
 if ( ( xmlStrQEqual ( prefix , name , entry -> name ) ) && ( xmlStrQEqual ( prefix2 , name2 , entry -> name2 ) ) && ( xmlStrQEqual ( prefix3 , name3 , entry -> name3 ) ) ) return ( entry -> payload ) ;
 }
 return ( NULL ) ;
 }