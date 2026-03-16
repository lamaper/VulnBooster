int archive_mstring_update_utf8 ( struct archive * a , struct archive_mstring * aes , const char * utf8 ) {
 struct archive_string_conv * sc ;
 int r ;
 if ( utf8 == NULL ) {
 aes -> aes_set = 0 ;
 return ( 0 ) ;
 }
 archive_strcpy ( & ( aes -> aes_utf8 ) , utf8 ) ;
 archive_string_empty ( & ( aes -> aes_mbs ) ) ;
 archive_wstring_empty ( & ( aes -> aes_wcs ) ) ;
 aes -> aes_set = AES_SET_UTF8 ;
 sc = archive_string_conversion_from_charset ( a , "UTF-8" , 1 ) ;
 if ( sc == NULL ) return ( - 1 ) ;
 r = archive_strcpy_l ( & ( aes -> aes_mbs ) , utf8 , sc ) ;
 if ( a == NULL ) free_sconv_object ( sc ) ;
 if ( r != 0 ) return ( - 1 ) ;
 aes -> aes_set = AES_SET_UTF8 | AES_SET_MBS ;
 if ( archive_wstring_append_from_mbs ( & ( aes -> aes_wcs ) , aes -> aes_mbs . s , aes -> aes_mbs . length ) ) return ( - 1 ) ;
 aes -> aes_set = AES_SET_UTF8 | AES_SET_WCS | AES_SET_MBS ;
 return ( 0 ) ;
 }