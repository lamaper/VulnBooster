Node * make_and_qual ( Node * qual1 , Node * qual2 ) {
 if ( qual1 == NULL ) return qual2 ;
 if ( qual2 == NULL ) return qual1 ;
 return ( Node * ) make_andclause ( list_make2 ( qual1 , qual2 ) ) ;
 }