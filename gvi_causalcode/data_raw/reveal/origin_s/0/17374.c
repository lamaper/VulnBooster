int xmlHashAddEntry2 ( xmlHashTablePtr table , const xmlChar * name , const xmlChar * name2 , void * userdata ) {
 return ( xmlHashAddEntry3 ( table , name , name2 , NULL , userdata ) ) ;
 }