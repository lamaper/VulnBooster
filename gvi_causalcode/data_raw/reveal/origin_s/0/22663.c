void * xmlHashQLookup ( xmlHashTablePtr table , const xmlChar * prefix , const xmlChar * name ) {
 return ( xmlHashQLookup3 ( table , prefix , name , NULL , NULL , NULL , NULL ) ) ;
 }