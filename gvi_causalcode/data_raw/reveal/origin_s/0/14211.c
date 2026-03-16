int archive_mstring_get_wcs ( struct archive * a , struct archive_mstring * aes , const wchar_t * * wp ) {
 int r , ret = 0 ;
 ( void ) a ;
 if ( aes -> aes_set & AES_SET_WCS ) {
 * wp = aes -> aes_wcs . s ;
 return ( ret ) ;
 }
 * wp = NULL ;
 if ( aes -> aes_set & AES_SET_MBS ) {
 archive_wstring_empty ( & ( aes -> aes_wcs ) ) ;
 r = archive_wstring_append_from_mbs ( & ( aes -> aes_wcs ) , aes -> aes_mbs . s , aes -> aes_mbs . length ) ;
 if ( r == 0 ) {
 aes -> aes_set |= AES_SET_WCS ;
 * wp = aes -> aes_wcs . s ;
 }
 else ret = - 1 ;
 }
 return ( ret ) ;
 }