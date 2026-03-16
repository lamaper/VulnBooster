char * TSAIOBufGet ( TSAIOCallback data ) {
 AIOCallback * pAIO = ( AIOCallback * ) data ;
 return ( char * ) pAIO -> aiocb . aio_buf ;
 }