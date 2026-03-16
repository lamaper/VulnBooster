void * xmlHashLookup ( xmlHashTablePtr table , const xmlChar * name ) {
 return ( xmlHashLookup3 ( table , name , NULL , NULL ) ) ;
 }