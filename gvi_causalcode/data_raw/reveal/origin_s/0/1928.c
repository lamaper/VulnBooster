rfbClientPtr rfbClientIteratorNext ( rfbClientIteratorPtr i ) {
 if ( i -> next == 0 ) {
 LOCK ( rfbClientListMutex ) ;
 i -> next = i -> screen -> clientHead ;
 UNLOCK ( rfbClientListMutex ) ;
 }
 else {
 IF_PTHREADS ( rfbClientPtr cl = i -> next ) ;
 i -> next = i -> next -> next ;
 IF_PTHREADS ( rfbDecrClientRef ( cl ) ) ;
 }

 if ( i -> next ) rfbIncrClientRef ( i -> next ) ;

 }