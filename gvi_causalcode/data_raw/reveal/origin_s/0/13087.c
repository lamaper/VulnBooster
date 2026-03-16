void rfbClientListInit ( rfbScreenInfoPtr rfbScreen ) {
 if ( sizeof ( rfbBool ) != 1 ) {
 fprintf ( stderr , "rfbBool's size is not 1 (%d)!\n" , ( int ) sizeof ( rfbBool ) ) ;
 exit ( 1 ) ;
 }
 rfbScreen -> clientHead = NULL ;
 INIT_MUTEX ( rfbClientListMutex ) ;
 }