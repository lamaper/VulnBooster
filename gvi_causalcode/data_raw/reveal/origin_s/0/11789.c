void * xmlHashQLookup2 ( xmlHashTablePtr table , const xmlChar * prefix , const xmlChar * name , const xmlChar * prefix2 , const xmlChar * name2 ) {
 return ( xmlHashQLookup3 ( table , prefix , name , prefix2 , name2 , NULL , NULL ) ) ;
 }