static struct archive_string_conv * create_sconv_object ( const char * fc , const char * tc , unsigned current_codepage , int flag ) {
 struct archive_string_conv * sc ;
 sc = calloc ( 1 , sizeof ( * sc ) ) ;
 if ( sc == NULL ) return ( NULL ) ;
 sc -> next = NULL ;
 sc -> from_charset = strdup ( fc ) ;
 if ( sc -> from_charset == NULL ) {
 free ( sc ) ;
 return ( NULL ) ;
 }
 sc -> to_charset = strdup ( tc ) ;
 if ( sc -> to_charset == NULL ) {
 free ( sc -> from_charset ) ;
 free ( sc ) ;
 return ( NULL ) ;
 }
 archive_string_init ( & sc -> utftmp ) ;
 if ( flag & SCONV_TO_CHARSET ) {
 sc -> from_cp = current_codepage ;
 sc -> to_cp = make_codepage_from_charset ( tc ) ;


 else if ( flag & SCONV_FROM_CHARSET ) {
 sc -> to_cp = current_codepage ;
 sc -> from_cp = make_codepage_from_charset ( fc ) ;


 if ( strcmp ( fc , tc ) == 0 || ( sc -> from_cp != ( unsigned ) - 1 && sc -> from_cp == sc -> to_cp ) ) sc -> same = 1 ;
 else sc -> same = 0 ;
 if ( strcmp ( tc , "UTF-8" ) == 0 ) flag |= SCONV_TO_UTF8 ;
 else if ( strcmp ( tc , "UTF-16BE" ) == 0 ) flag |= SCONV_TO_UTF16BE ;
 else if ( strcmp ( tc , "UTF-16LE" ) == 0 ) flag |= SCONV_TO_UTF16LE ;
 if ( strcmp ( fc , "UTF-8" ) == 0 ) flag |= SCONV_FROM_UTF8 ;
 else if ( strcmp ( fc , "UTF-16BE" ) == 0 ) flag |= SCONV_FROM_UTF16BE ;
 else if ( strcmp ( fc , "UTF-16LE" ) == 0 ) flag |= SCONV_FROM_UTF16LE ;

 else if ( sc -> to_cp == CP_UTF16BE ) flag |= SCONV_TO_UTF16BE | SCONV_WIN_CP ;
 else if ( sc -> to_cp == CP_UTF16LE ) flag |= SCONV_TO_UTF16LE | SCONV_WIN_CP ;
 if ( sc -> from_cp == CP_UTF8 ) flag |= SCONV_FROM_UTF8 ;
 else if ( sc -> from_cp == CP_UTF16BE ) flag |= SCONV_FROM_UTF16BE | SCONV_WIN_CP ;
 else if ( sc -> from_cp == CP_UTF16LE ) flag |= SCONV_FROM_UTF16LE | SCONV_WIN_CP ;


 else # endif flag |= SCONV_NORMALIZATION_C ;
 }

 if ( ( flag & SCONV_FROM_CHARSET ) && ! ( flag & ( SCONV_FROM_UTF16 | SCONV_FROM_UTF8 ) ) && ( flag & SCONV_TO_UTF8 ) ) flag |= SCONV_NORMALIZATION_D ;

 if ( ( ( flag & ( SCONV_TO_UTF8 | SCONV_TO_UTF16 ) ) && ( flag & ( SCONV_FROM_UTF8 | SCONV_FROM_UTF16 ) ) ) || ( flag & SCONV_WIN_CP ) ) {
 sc -> cd = ( iconv_t ) - 1 ;
 }
 else {
 sc -> cd = iconv_open ( tc , fc ) ;
 if ( sc -> cd == ( iconv_t ) - 1 && ( sc -> flag & SCONV_BEST_EFFORT ) ) {
 if ( strcmp ( tc , "CP932" ) == 0 ) sc -> cd = iconv_open ( "SJIS" , fc ) ;
 else if ( strcmp ( fc , "CP932" ) == 0 ) sc -> cd = iconv_open ( tc , "SJIS" ) ;
 }

 sc -> cd_w = iconv_open ( "UTF-8" , fc ) ;
 if ( sc -> cd_w == ( iconv_t ) - 1 && ( sc -> flag & SCONV_BEST_EFFORT ) ) {
 if ( strcmp ( fc , "CP932" ) == 0 ) sc -> cd_w = iconv_open ( "UTF-8" , "SJIS" ) ;
 }
 }


 setup_converter ( sc ) ;
 return ( sc ) ;
 }