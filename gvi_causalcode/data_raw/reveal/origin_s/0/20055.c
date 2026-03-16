static gcry_err_code_t pss_encode ( gcry_mpi_t * r_result , unsigned int nbits , int algo , const unsigned char * value , size_t valuelen , int saltlen , const void * random_override , size_t random_override_len ) {
 gcry_err_code_t rc = 0 ;
 gcry_error_t err ;
 size_t hlen ;
 unsigned char * em = NULL ;
 size_t emlen = ( nbits + 7 ) / 8 ;
 unsigned char * h ;
 unsigned char * buf = NULL ;
 size_t buflen ;
 unsigned char * mhash ;
 unsigned char * salt ;
 unsigned char * dbmask ;
 unsigned char * p ;
 size_t n ;
 hlen = gcry_md_get_algo_dlen ( algo ) ;
 gcry_assert ( hlen ) ;
 buflen = 8 + hlen + saltlen + ( emlen - hlen - 1 ) ;
 buf = gcry_malloc ( buflen ) ;
 if ( ! buf ) {
 rc = gpg_err_code_from_syserror ( ) ;
 goto leave ;
 }
 mhash = buf + 8 ;
 salt = mhash + hlen ;
 dbmask = salt + saltlen ;
 if ( valuelen != hlen ) {
 rc = GPG_ERR_INV_LENGTH ;
 goto leave ;
 }
 memcpy ( mhash , value , hlen ) ;
 if ( emlen < hlen + saltlen + 2 ) {
 rc = GPG_ERR_TOO_SHORT ;
 goto leave ;
 }
 em = gcry_malloc ( emlen ) ;
 if ( ! em ) {
 rc = gpg_err_code_from_syserror ( ) ;
 goto leave ;
 }
 h = em + emlen - 1 - hlen ;
 if ( saltlen ) {
 if ( random_override ) {
 if ( random_override_len != saltlen ) {
 rc = GPG_ERR_INV_ARG ;
 goto leave ;
 }
 memcpy ( salt , random_override , saltlen ) ;
 }
 else gcry_randomize ( salt , saltlen , GCRY_STRONG_RANDOM ) ;
 }
 memset ( buf , 0 , 8 ) ;
 gcry_md_hash_buffer ( algo , h , buf , 8 + hlen + saltlen ) ;
 p = em + emlen - 1 - hlen - saltlen - 1 ;
 memset ( em , 0 , p - em ) ;
 * p ++ = 0x01 ;
 memcpy ( p , salt , saltlen ) ;
 mgf1 ( dbmask , emlen - hlen - 1 , h , hlen , algo ) ;
 for ( n = 0 , p = dbmask ;
 n < emlen - hlen - 1 ;
 n ++ , p ++ ) em [ n ] ^= * p ;
 em [ 0 ] &= 0xFF >> ( 8 * emlen - nbits ) ;
 em [ emlen - 1 ] = 0xbc ;
 err = gcry_mpi_scan ( r_result , GCRYMPI_FMT_USG , em , emlen , NULL ) ;
 if ( err ) rc = gcry_err_code ( err ) ;
 else if ( DBG_CIPHER ) log_mpidump ( "PSS encoded data" , * r_result ) ;
 leave : if ( em ) {
 wipememory ( em , emlen ) ;
 gcry_free ( em ) ;
 }
 if ( buf ) {
 wipememory ( buf , buflen ) ;
 gcry_free ( buf ) ;
 }
 return rc ;
 }