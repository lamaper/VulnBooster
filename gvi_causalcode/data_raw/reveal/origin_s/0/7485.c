void rfbClientConnectionGone ( rfbClientPtr cl ) {


 if ( cl -> prev ) cl -> prev -> next = cl -> next ;
 else cl -> screen -> clientHead = cl -> next ;
 if ( cl -> next ) cl -> next -> prev = cl -> prev ;
 UNLOCK ( rfbClientListMutex ) ;

 int i ;
 do {
 LOCK ( cl -> refCountMutex ) ;
 i = cl -> refCount ;
 if ( i > 0 ) WAIT ( cl -> deleteCond , cl -> refCountMutex ) ;
 UNLOCK ( cl -> refCountMutex ) ;
 }
 while ( i > 0 ) ;
 }

 if ( cl -> scaledScreen != NULL ) cl -> scaledScreen -> scaledScreenRefCount -- ;


 free ( cl -> beforeEncBuf ) ;
 free ( cl -> afterEncBuf ) ;
 if ( cl -> sock >= 0 ) FD_CLR ( cl -> sock , & ( cl -> screen -> allFds ) ) ;
 cl -> clientGoneHook ( cl ) ;
 rfbLog ( "Client %s gone\n" , cl -> host ) ;
 free ( cl -> host ) ;

 deflateEnd ( & ( cl -> compStream ) ) ;
 }

 i < 4 ;
 i ++ ) {
 if ( cl -> zsActive [ i ] ) deflateEnd ( & cl -> zsStruct [ i ] ) ;
 }

 sraRgnDestroy ( cl -> modifiedRegion ) ;
 sraRgnDestroy ( cl -> requestedRegion ) ;
 sraRgnDestroy ( cl -> copyRegion ) ;
 if ( cl -> translateLookupTable ) free ( cl -> translateLookupTable ) ;
 TINI_COND ( cl -> updateCond ) ;
 TINI_MUTEX ( cl -> updateMutex ) ;
 LOCK ( cl -> outputMutex ) ;
 UNLOCK ( cl -> outputMutex ) ;
 TINI_MUTEX ( cl -> outputMutex ) ;
 LOCK ( cl -> sendMutex ) ;
 UNLOCK ( cl -> sendMutex ) ;
 TINI_MUTEX ( cl -> sendMutex ) ;
 rfbPrintStats ( cl ) ;
 rfbResetStats ( cl ) ;
 free ( cl ) ;
 }