TSReturnCode TSAIORead ( int fd , off_t offset , char * buf , size_t buffSize , TSCont contp ) {
 sdk_assert ( sdk_sanity_check_iocore_structure ( contp ) == TS_SUCCESS ) ;
 Continuation * pCont = ( Continuation * ) contp ;
 AIOCallback * pAIO = new_AIOCallback ( ) ;
 if ( pAIO == nullptr ) {
 return TS_ERROR ;
 }
 pAIO -> aiocb . aio_fildes = fd ;
 pAIO -> aiocb . aio_offset = offset ;
 pAIO -> aiocb . aio_nbytes = buffSize ;
 pAIO -> aiocb . aio_buf = buf ;
 pAIO -> action = pCont ;
 pAIO -> thread = pCont -> mutex -> thread_holding ;
 if ( ink_aio_read ( pAIO , 1 ) == 1 ) {
 return TS_SUCCESS ;
 }
 return TS_ERROR ;
 }