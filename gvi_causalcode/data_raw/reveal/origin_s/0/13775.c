static gcry_err_code_t pss_verify ( gcry_mpi_t value , gcry_mpi_t encoded , unsigned int nbits , int algo , size_t saltlen ) {
 gcry_err_code_t rc = 0 ;
 size_t hlen ;
 unsigned char * em = NULL ;
 size_t emlen = ( nbits + 7 ) / 8 ;
 unsigned char * salt ;
 unsigned char * h ;
 unsigned char * buf = NULL ;
 size_t buflen ;
 unsigned char * dbmask ;
 unsigned char * mhash ;
 unsigned char * p ;
 size_t n ;
 hlen = gcry_md_get_algo_dlen ( algo ) ;
 gcry_assert ( hlen ) ;
 buflen = 8 + hlen + saltlen ;
 if ( buflen < emlen - hlen - 1 ) buflen = emlen - hlen - 1 ;
 buflen += hlen ;
 buf = gcry_malloc ( buflen ) ;
 if ( ! buf ) {
 rc = gpg_err_code_from_syserror ( ) ;
 goto leave ;
 }
 dbmask = buf ;
 mhash = buf + buflen - hlen ;
 rc = octet_string_from_mpi ( NULL , mhash , value , hlen ) ;
 if ( rc ) goto leave ;
 rc = octet_string_from_mpi ( & em , NULL , encoded , emlen ) ;
 if ( rc ) goto leave ;
 if ( emlen < hlen + saltlen + 2 ) {
 rc = GPG_ERR_TOO_SHORT ;
 goto leave ;
 }
 if ( em [ emlen - 1 ] != 0xbc ) {
 rc = GPG_ERR_BAD_SIGNATURE ;
 goto leave ;
 }
 h = em + emlen - 1 - hlen ;
 if ( ( em [ 0 ] & ~ ( 0xFF >> ( 8 * emlen - nbits ) ) ) ) {
 rc = GPG_ERR_BAD_SIGNATURE ;
 goto leave ;
 }
 mgf1 ( dbmask , emlen - hlen - 1 , h , hlen , algo ) ;
 for ( n = 0 , p = dbmask ;
 n < emlen - hlen - 1 ;
 n ++ , p ++ ) em [ n ] ^= * p ;
 em [ 0 ] &= 0xFF >> ( 8 * emlen - nbits ) ;
 for ( n = 0 ;
 n < emlen - hlen - saltlen - 2 && ! em [ n ] ;
 n ++ ) ;
 if ( n != emlen - hlen - saltlen - 2 || em [ n ++ ] != 1 ) {
 rc = GPG_ERR_BAD_SIGNATURE ;
 goto leave ;
 }
 salt = em + n ;
 memset ( buf , 0 , 8 ) ;
 memcpy ( buf + 8 , mhash , hlen ) ;
 memcpy ( buf + 8 + hlen , salt , saltlen ) ;
 gcry_md_hash_buffer ( algo , buf , buf , 8 + hlen + saltlen ) ;
 rc = memcmp ( h , buf , hlen ) ? GPG_ERR_BAD_SIGNATURE : GPG_ERR_NO_ERROR ;
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