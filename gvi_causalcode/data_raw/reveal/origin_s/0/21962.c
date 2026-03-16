int xmlHashUpdateEntry ( xmlHashTablePtr table , const xmlChar * name , void * userdata , xmlHashDeallocator f ) {
 return ( xmlHashUpdateEntry3 ( table , name , NULL , NULL , userdata , f ) ) ;
 }