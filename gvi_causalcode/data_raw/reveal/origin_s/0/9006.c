static gcry_err_code_t mgf1 ( unsigned char * output , size_t outlen , unsigned char * seed , size_t seedlen , int algo ) {
 size_t dlen , nbytes , n ;
 int idx ;
 gcry_md_hd_t hd ;
 gcry_error_t err ;
 err = gcry_md_open ( & hd , algo , 0 ) ;
 if ( err ) return gpg_err_code ( err ) ;
 dlen = gcry_md_get_algo_dlen ( algo ) ;
 nbytes = 0 ;
 idx = 0 ;
 while ( nbytes < outlen ) {
 unsigned char c [ 4 ] , * digest ;
 if ( idx ) gcry_md_reset ( hd ) ;
 c [ 0 ] = ( idx >> 24 ) & 0xFF ;
 c [ 1 ] = ( idx >> 16 ) & 0xFF ;
 c [ 2 ] = ( idx >> 8 ) & 0xFF ;
 c [ 3 ] = idx & 0xFF ;
 idx ++ ;
 gcry_md_write ( hd , seed , seedlen ) ;
 gcry_md_write ( hd , c , 4 ) ;
 digest = gcry_md_read ( hd , 0 ) ;
 n = ( outlen - nbytes < dlen ) ? ( outlen - nbytes ) : dlen ;
 memcpy ( output + nbytes , digest , n ) ;
 nbytes += n ;
 }
 gcry_md_close ( hd ) ;
 return GPG_ERR_NO_ERROR ;
 }