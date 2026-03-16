static gcry_err_code_t oaep_encode ( gcry_mpi_t * r_result , unsigned int nbits , int algo , const unsigned char * value , size_t valuelen , const unsigned char * label , size_t labellen , const void * random_override , size_t random_override_len ) {
 gcry_err_code_t rc = 0 ;
 gcry_error_t err ;
 unsigned char * frame = NULL ;
 size_t nframe = ( nbits + 7 ) / 8 ;
 unsigned char * p ;
 size_t hlen ;
 size_t n ;
 * r_result = NULL ;
 if ( ! label || ! labellen ) {
 label = ( const unsigned char * ) "" ;
 labellen = 0 ;
 }
 hlen = gcry_md_get_algo_dlen ( algo ) ;
 if ( valuelen > nframe - 2 * hlen - 2 || ! nframe ) {
 return GPG_ERR_TOO_SHORT ;
 }
 frame = gcry_calloc_secure ( 1 , nframe ) ;
 if ( ! frame ) return gpg_err_code_from_syserror ( ) ;
 gcry_md_hash_buffer ( algo , frame + 1 + hlen , label , labellen ) ;
 n = nframe - valuelen - 1 ;
 frame [ n ] = 0x01 ;
 memcpy ( frame + n + 1 , value , valuelen ) ;
 if ( random_override ) {
 if ( random_override_len != hlen ) {
 gcry_free ( frame ) ;
 return GPG_ERR_INV_ARG ;
 }
 memcpy ( frame + 1 , random_override , hlen ) ;
 }
 else gcry_randomize ( frame + 1 , hlen , GCRY_STRONG_RANDOM ) ;
 {
 unsigned char * dmask ;
 dmask = gcry_malloc_secure ( nframe - hlen - 1 ) ;
 if ( ! dmask ) {
 rc = gpg_err_code_from_syserror ( ) ;
 gcry_free ( frame ) ;
 return rc ;
 }
 rc = mgf1 ( dmask , nframe - hlen - 1 , frame + 1 , hlen , algo ) ;
 if ( rc ) {
 gcry_free ( dmask ) ;
 gcry_free ( frame ) ;
 return rc ;
 }
 for ( n = 1 + hlen , p = dmask ;
 n < nframe ;
 n ++ ) frame [ n ] ^= * p ++ ;
 gcry_free ( dmask ) ;
 }
 {
 unsigned char * smask ;
 smask = gcry_malloc_secure ( hlen ) ;
 if ( ! smask ) {
 rc = gpg_err_code_from_syserror ( ) ;
 gcry_free ( frame ) ;
 return rc ;
 }
 rc = mgf1 ( smask , hlen , frame + 1 + hlen , nframe - hlen - 1 , algo ) ;
 if ( rc ) {
 gcry_free ( smask ) ;
 gcry_free ( frame ) ;
 return rc ;
 }
 for ( n = 1 , p = smask ;
 n < 1 + hlen ;
 n ++ ) frame [ n ] ^= * p ++ ;
 gcry_free ( smask ) ;
 }
 err = gcry_mpi_scan ( r_result , GCRYMPI_FMT_USG , frame , nframe , NULL ) ;
 if ( err ) rc = gcry_err_code ( err ) ;
 else if ( DBG_CIPHER ) log_mpidump ( "OAEP encoded data" , * r_result ) ;
 gcry_free ( frame ) ;
 return rc ;
 }