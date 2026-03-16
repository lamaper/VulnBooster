int archive_mstring_copy_mbs_len_l ( struct archive_mstring * aes , const char * mbs , size_t len , struct archive_string_conv * sc ) {
 int r ;
 if ( mbs == NULL ) {
 aes -> aes_set = 0 ;
 return ( 0 ) ;
 }
 archive_string_empty ( & ( aes -> aes_mbs ) ) ;
 archive_wstring_empty ( & ( aes -> aes_wcs ) ) ;
 archive_string_empty ( & ( aes -> aes_utf8 ) ) ;

 if ( archive_string_append ( & ( aes -> aes_mbs ) , mbs , mbsnbytes ( mbs , len ) ) == NULL ) {
 aes -> aes_set = 0 ;
 r = - 1 ;
 }
 else {
 aes -> aes_set = AES_SET_MBS ;
 r = 0 ;
 }

 else if ( sc != NULL && sc -> cd_w != ( iconv_t ) - 1 ) {
 iconv_t cd = sc -> cd ;
 unsigned from_cp ;
 int flag ;
 sc -> cd = sc -> cd_w ;
 r = archive_strncpy_l ( & ( aes -> aes_utf8 ) , mbs , len , sc ) ;
 sc -> cd = cd ;
 if ( r != 0 ) {
 aes -> aes_set = 0 ;
 return ( r ) ;
 }
 aes -> aes_set = AES_SET_UTF8 ;
 flag = sc -> flag ;
 sc -> flag &= ~ ( SCONV_NORMALIZATION_C | SCONV_TO_UTF16 | SCONV_FROM_UTF16 ) ;
 from_cp = sc -> from_cp ;
 sc -> from_cp = CP_UTF8 ;
 r = archive_wstring_append_from_mbs_in_codepage ( & ( aes -> aes_wcs ) , aes -> aes_utf8 . s , aes -> aes_utf8 . length , sc ) ;
 sc -> flag = flag ;
 sc -> from_cp = from_cp ;
 if ( r == 0 ) aes -> aes_set |= AES_SET_WCS ;

 else {
 r = archive_wstring_append_from_mbs_in_codepage ( & ( aes -> aes_wcs ) , mbs , len , sc ) ;
 if ( r == 0 ) aes -> aes_set = AES_SET_WCS ;
 else aes -> aes_set = 0 ;
 }

 if ( r == 0 ) aes -> aes_set = AES_SET_MBS ;
 else aes -> aes_set = 0 ;

 }