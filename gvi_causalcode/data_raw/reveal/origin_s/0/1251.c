static gcry_err_code_t pkcs1_encode_for_signature ( gcry_mpi_t * r_result , unsigned int nbits , const unsigned char * value , size_t valuelen , int algo ) {
 gcry_err_code_t rc = 0 ;
 gcry_error_t err ;
 byte asn [ 100 ] ;
 byte * frame = NULL ;
 size_t nframe = ( nbits + 7 ) / 8 ;
 int i ;
 size_t n ;
 size_t asnlen , dlen ;
 asnlen = DIM ( asn ) ;
 dlen = gcry_md_get_algo_dlen ( algo ) ;
 if ( gcry_md_algo_info ( algo , GCRYCTL_GET_ASNOID , asn , & asnlen ) ) {
 return GPG_ERR_NOT_IMPLEMENTED ;
 }
 if ( valuelen != dlen ) {
 return GPG_ERR_CONFLICT ;
 }
 if ( ! dlen || dlen + asnlen + 4 > nframe ) {
 return GPG_ERR_TOO_SHORT ;
 }
 if ( ! ( frame = gcry_malloc ( nframe ) ) ) return gpg_err_code_from_syserror ( ) ;
 n = 0 ;
 frame [ n ++ ] = 0 ;
 frame [ n ++ ] = 1 ;
 i = nframe - valuelen - asnlen - 3 ;
 gcry_assert ( i > 1 ) ;
 memset ( frame + n , 0xff , i ) ;
 n += i ;
 frame [ n ++ ] = 0 ;
 memcpy ( frame + n , asn , asnlen ) ;
 n += asnlen ;
 memcpy ( frame + n , value , valuelen ) ;
 n += valuelen ;
 gcry_assert ( n == nframe ) ;
 err = gcry_mpi_scan ( r_result , GCRYMPI_FMT_USG , frame , n , & nframe ) ;
 if ( err ) rc = gcry_err_code ( err ) ;
 else if ( DBG_CIPHER ) log_mpidump ( "PKCS#1 block type 1 encoded data" , * r_result ) ;
 gcry_free ( frame ) ;
 return rc ;
 }