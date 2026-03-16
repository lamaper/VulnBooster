TSReturnCode TSAIOWrite ( int fd , off_t offset , char * buf , const size_t bufSize , TSCont contp ) {
 sdk_assert ( sdk_sanity_check_iocore_structure ( contp ) == TS_SUCCESS ) ;
 Continuation * pCont = ( Continuation * ) contp ;
 AIOCallback * pAIO = new_AIOCallback ( ) ;
 sdk_assert ( sdk_sanity_check_null_ptr ( ( void * ) pAIO ) == TS_SUCCESS ) ;
 pAIO -> aiocb . aio_fildes = fd ;
 pAIO -> aiocb . aio_offset = offset ;
 pAIO -> aiocb . aio_buf = buf ;
 pAIO -> aiocb . aio_nbytes = bufSize ;
 pAIO -> action = pCont ;
 pAIO -> thread = pCont -> mutex -> thread_holding ;
 if ( ink_aio_write ( pAIO , 1 ) == 1 ) {
 return TS_SUCCESS ;
 }
 return TS_ERROR ;
 }