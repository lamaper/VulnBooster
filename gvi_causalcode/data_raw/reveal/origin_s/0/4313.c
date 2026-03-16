static void free_sconv_object ( struct archive_string_conv * sc ) {
 free ( sc -> from_charset ) ;
 free ( sc -> to_charset ) ;
 archive_string_free ( & sc -> utftmp ) ;

 if ( sc -> cd_w != ( iconv_t ) - 1 ) iconv_close ( sc -> cd_w ) ;

 }