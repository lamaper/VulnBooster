static gcry_err_code_t pkcs1_decode_for_encryption ( unsigned char * * r_result , size_t * r_resultlen , unsigned int nbits , gcry_mpi_t value ) {
 gcry_error_t err ;
 unsigned char * frame = NULL ;
 size_t nframe = ( nbits + 7 ) / 8 ;
 size_t n ;
 * r_result = NULL ;
 if ( ! ( frame = gcry_malloc_secure ( nframe ) ) ) return gpg_err_code_from_syserror ( ) ;
 err = gcry_mpi_print ( GCRYMPI_FMT_USG , frame , nframe , & n , value ) ;
 if ( err ) {
 gcry_free ( frame ) ;
 return gcry_err_code ( err ) ;
 }
 nframe = n ;
 if ( nframe < 4 ) {
 gcry_free ( frame ) ;
 return GPG_ERR_ENCODING_PROBLEM ;
 }
 n = 0 ;
 if ( ! frame [ 0 ] ) n ++ ;
 if ( frame [ n ++ ] != 0x02 ) {
 gcry_free ( frame ) ;
 return GPG_ERR_ENCODING_PROBLEM ;
 }
 for ( ;
 n < nframe && frame [ n ] != 0x00 ;
 n ++ ) ;
 if ( n + 1 >= nframe ) {
 gcry_free ( frame ) ;
 return GPG_ERR_ENCODING_PROBLEM ;
 }
 n ++ ;
 memmove ( frame , frame + n , nframe - n ) ;
 * r_result = frame ;
 * r_resultlen = nframe - n ;
 if ( DBG_CIPHER ) log_printhex ( "value extracted from PKCS#1 block type 2 encoded data" , * r_result , * r_resultlen ) ;
 return 0 ;
 }