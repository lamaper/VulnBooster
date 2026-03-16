int TSAIONBytesGet ( TSAIOCallback data ) {
 AIOCallback * pAIO = ( AIOCallback * ) data ;
 return ( int ) pAIO -> aio_result ;
 }