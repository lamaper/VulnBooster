int xmlHashAddEntry3 ( xmlHashTablePtr table , const xmlChar * name , const xmlChar * name2 , const xmlChar * name3 , void * userdata ) {
 unsigned long key , len = 0 ;
 xmlHashEntryPtr entry ;
 xmlHashEntryPtr insert ;
 if ( ( table == NULL ) || ( name == NULL ) ) return ( - 1 ) ;
 if ( table -> dict ) {
 if ( ! xmlDictOwns ( table -> dict , name ) ) {
 name = xmlDictLookup ( table -> dict , name , - 1 ) ;
 if ( name == NULL ) return ( - 1 ) ;
 }
 if ( ( name2 != NULL ) && ( ! xmlDictOwns ( table -> dict , name2 ) ) ) {
 name2 = xmlDictLookup ( table -> dict , name2 , - 1 ) ;
 if ( name2 == NULL ) return ( - 1 ) ;
 }
 if ( ( name3 != NULL ) && ( ! xmlDictOwns ( table -> dict , name3 ) ) ) {
 name3 = xmlDictLookup ( table -> dict , name3 , - 1 ) ;
 if ( name3 == NULL ) return ( - 1 ) ;
 }
 }
 key = xmlHashComputeKey ( table , name , name2 , name3 ) ;
 if ( table -> table [ key ] . valid == 0 ) {
 insert = NULL ;
 }
 else {
 if ( table -> dict ) {
 for ( insert = & ( table -> table [ key ] ) ;
 insert -> next != NULL ;
 insert = insert -> next ) {
 if ( ( insert -> name == name ) && ( insert -> name2 == name2 ) && ( insert -> name3 == name3 ) ) return ( - 1 ) ;
 len ++ ;
 }
 if ( ( insert -> name == name ) && ( insert -> name2 == name2 ) && ( insert -> name3 == name3 ) ) return ( - 1 ) ;
 }
 else {
 for ( insert = & ( table -> table [ key ] ) ;
 insert -> next != NULL ;
 insert = insert -> next ) {
 if ( ( xmlStrEqual ( insert -> name , name ) ) && ( xmlStrEqual ( insert -> name2 , name2 ) ) && ( xmlStrEqual ( insert -> name3 , name3 ) ) ) return ( - 1 ) ;
 len ++ ;
 }
 if ( ( xmlStrEqual ( insert -> name , name ) ) && ( xmlStrEqual ( insert -> name2 , name2 ) ) && ( xmlStrEqual ( insert -> name3 , name3 ) ) ) return ( - 1 ) ;
 }
 }
 if ( insert == NULL ) {
 entry = & ( table -> table [ key ] ) ;
 }
 else {
 entry = xmlMalloc ( sizeof ( xmlHashEntry ) ) ;
 if ( entry == NULL ) return ( - 1 ) ;
 }
 if ( table -> dict != NULL ) {
 entry -> name = ( xmlChar * ) name ;
 entry -> name2 = ( xmlChar * ) name2 ;
 entry -> name3 = ( xmlChar * ) name3 ;
 }
 else {
 entry -> name = xmlStrdup ( name ) ;
 entry -> name2 = xmlStrdup ( name2 ) ;
 entry -> name3 = xmlStrdup ( name3 ) ;
 }
 entry -> payload = userdata ;
 entry -> next = NULL ;
 entry -> valid = 1 ;
 if ( insert != NULL ) insert -> next = entry ;
 table -> nbElems ++ ;
 if ( len > MAX_HASH_LEN ) xmlHashGrow ( table , MAX_HASH_LEN * table -> size ) ;
 return ( 0 ) ;
 }