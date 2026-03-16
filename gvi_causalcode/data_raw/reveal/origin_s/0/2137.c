int xmlHashRemoveEntry ( xmlHashTablePtr table , const xmlChar * name , xmlHashDeallocator f ) {
 return ( xmlHashRemoveEntry3 ( table , name , NULL , NULL , f ) ) ;
 }