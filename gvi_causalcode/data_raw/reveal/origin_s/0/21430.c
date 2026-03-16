int xmlHashRemoveEntry2 ( xmlHashTablePtr table , const xmlChar * name , const xmlChar * name2 , xmlHashDeallocator f ) {
 return ( xmlHashRemoveEntry3 ( table , name , name2 , NULL , f ) ) ;
 }