static gcry_err_code_t oaep_decode ( unsigned char * * r_result , size_t * r_resultlen , unsigned int nbits , int algo , gcry_mpi_t value , const unsigned char * label , size_t labellen ) {
 gcry_err_code_t rc ;
 unsigned char * frame = NULL ;
 unsigned char * masked_seed ;
 unsigned char * masked_db ;
 unsigned char * seed = NULL ;
 unsigned char * db ;
 unsigned char * lhash = NULL ;
 size_t nframe ;
 size_t hlen ;
 size_t db_len ;
 size_t nkey = ( nbits + 7 ) / 8 ;
 int failed = 0 ;
 size_t n ;
 * r_result = NULL ;
 if ( ! label || ! labellen ) {
 label = ( const unsigned char * ) "" ;
 labellen = 0 ;
 }
 hlen = gcry_md_get_algo_dlen ( algo ) ;
 lhash = gcry_malloc ( hlen ) ;
 if ( ! lhash ) return gpg_err_code_from_syserror ( ) ;
 gcry_md_hash_buffer ( algo , lhash , label , labellen ) ;
 rc = octet_string_from_mpi ( & frame , NULL , value , nkey ) ;
 if ( rc ) {
 gcry_free ( lhash ) ;
 return GPG_ERR_ENCODING_PROBLEM ;
 }
 nframe = nkey ;
 if ( nframe < 2 * hlen + 2 ) {
 gcry_free ( frame ) ;
 gcry_free ( lhash ) ;
 return GPG_ERR_ENCODING_PROBLEM ;
 }
 seed = gcry_malloc_secure ( nframe - 1 ) ;
 if ( ! seed ) {
 rc = gpg_err_code_from_syserror ( ) ;
 gcry_free ( frame ) ;
 gcry_free ( lhash ) ;
 return rc ;
 }
 db = seed + hlen ;
 masked_seed = frame + 1 ;
 masked_db = frame + 1 + hlen ;
 db_len = nframe - 1 - hlen ;
 if ( mgf1 ( seed , hlen , masked_db , db_len , algo ) ) failed = 1 ;
 for ( n = 0 ;
 n < hlen ;
 n ++ ) seed [ n ] ^= masked_seed [ n ] ;
 if ( mgf1 ( db , db_len , seed , hlen , algo ) ) failed = 1 ;
 for ( n = 0 ;
 n < db_len ;
 n ++ ) db [ n ] ^= masked_db [ n ] ;
 if ( memcmp ( lhash , db , hlen ) ) failed = 1 ;
 for ( n = hlen ;
 n < db_len ;
 n ++ ) if ( db [ n ] == 0x01 ) break ;
 if ( n == db_len ) failed = 1 ;
 if ( frame [ 0 ] ) failed = 1 ;
 gcry_free ( lhash ) ;
 gcry_free ( frame ) ;
 if ( failed ) {
 gcry_free ( seed ) ;
 return GPG_ERR_ENCODING_PROBLEM ;
 }
 n ++ ;
 memmove ( seed , db + n , db_len - n ) ;
 * r_result = seed ;
 * r_resultlen = db_len - n ;
 seed = NULL ;
 if ( DBG_CIPHER ) log_printhex ( "value extracted from OAEP encoded data" , * r_result , * r_resultlen ) ;
 return 0 ;
 }