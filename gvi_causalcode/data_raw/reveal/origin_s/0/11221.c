int xmlHashUpdateEntry2 ( xmlHashTablePtr table , const xmlChar * name , const xmlChar * name2 , void * userdata , xmlHashDeallocator f ) {
 return ( xmlHashUpdateEntry3 ( table , name , name2 , NULL , userdata , f ) ) ;
 }