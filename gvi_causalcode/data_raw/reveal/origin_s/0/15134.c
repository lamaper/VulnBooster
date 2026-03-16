void * xmlHashLookup2 ( xmlHashTablePtr table , const xmlChar * name , const xmlChar * name2 ) {
 return ( xmlHashLookup3 ( table , name , name2 , NULL ) ) ;
 }