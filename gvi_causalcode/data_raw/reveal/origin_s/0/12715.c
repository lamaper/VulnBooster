int xmlHashAddEntry ( xmlHashTablePtr table , const xmlChar * name , void * userdata ) {
 return ( xmlHashAddEntry3 ( table , name , NULL , NULL , userdata ) ) ;
 }