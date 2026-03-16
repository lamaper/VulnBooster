rfbClientPtr rfbClientIteratorHead ( rfbClientIteratorPtr i ) {

 rfbDecrClientRef ( i -> next ) ;
 rfbIncrClientRef ( i -> screen -> clientHead ) ;
 }

 i -> next = i -> screen -> clientHead ;
 UNLOCK ( rfbClientListMutex ) ;
 return i -> next ;
 }