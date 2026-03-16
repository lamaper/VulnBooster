static gcry_err_code_t pkcs1_encode_for_encryption ( gcry_mpi_t * r_result , unsigned int nbits , const unsigned char * value , size_t valuelen , const unsigned char * random_override , size_t random_override_len ) {
 gcry_err_code_t rc = 0 ;
 gcry_error_t err ;
 unsigned char * frame = NULL ;
 size_t nframe = ( nbits + 7 ) / 8 ;
 int i ;
 size_t n ;
 unsigned char * p ;
 if ( valuelen + 7 > nframe || ! nframe ) {
 return GPG_ERR_TOO_SHORT ;
 }
 if ( ! ( frame = gcry_malloc_secure ( nframe ) ) ) return gpg_err_code_from_syserror ( ) ;
 n = 0 ;
 frame [ n ++ ] = 0 ;
 frame [ n ++ ] = 2 ;
 i = nframe - 3 - valuelen ;
 gcry_assert ( i > 0 ) ;
 if ( random_override ) {
 int j ;
 if ( random_override_len != i ) {
 gcry_free ( frame ) ;
 return GPG_ERR_INV_ARG ;
 }
 for ( j = 0 ;
 j < random_override_len ;
 j ++ ) if ( ! random_override [ j ] ) {
 gcry_free ( frame ) ;
 return GPG_ERR_INV_ARG ;
 }
 memcpy ( frame + n , random_override , random_override_len ) ;
 n += random_override_len ;
 }
 else {
 p = gcry_random_bytes_secure ( i , GCRY_STRONG_RANDOM ) ;
 for ( ;
 ;
 ) {
 int j , k ;
 unsigned char * pp ;
 for ( j = k = 0 ;
 j < i ;
 j ++ ) {
 if ( ! p [ j ] ) k ++ ;
 }
 if ( ! k ) break ;
 k += k / 128 + 3 ;
 pp = gcry_random_bytes_secure ( k , GCRY_STRONG_RANDOM ) ;
 for ( j = 0 ;
 j < i && k ;
 ) {
 if ( ! p [ j ] ) p [ j ] = pp [ -- k ] ;
 if ( p [ j ] ) j ++ ;
 }
 gcry_free ( pp ) ;
 }
 memcpy ( frame + n , p , i ) ;
 n += i ;
 gcry_free ( p ) ;
 }
 frame [ n ++ ] = 0 ;
 memcpy ( frame + n , value , valuelen ) ;
 n += valuelen ;
 gcry_assert ( n == nframe ) ;
 err = gcry_mpi_scan ( r_result , GCRYMPI_FMT_USG , frame , n , & nframe ) ;
 if ( err ) rc = gcry_err_code ( err ) ;
 else if ( DBG_CIPHER ) log_mpidump ( "PKCS#1 block type 2 encoded data" , * r_result ) ;
 gcry_free ( frame ) ;
 return rc ;
 }