bool hostname_requires_resolving ( const char * hostname ) {
 char cur ;
 if ( ! hostname ) return FALSE ;
 size_t namelen = strlen ( hostname ) ;
 size_t lhlen = strlen ( my_localhost ) ;
 if ( ( namelen == lhlen ) && ! my_strnncoll ( system_charset_info , ( const uchar * ) hostname , namelen , ( const uchar * ) my_localhost , strlen ( my_localhost ) ) ) return FALSE ;
 for ( ;
 ( cur = * hostname ) ;
 hostname ++ ) {
 if ( ( cur != '%' ) && ( cur != '_' ) && ( cur != '.' ) && ( cur != '/' ) && ( ( cur < '0' ) || ( cur > '9' ) ) ) return TRUE ;
 }
 return FALSE ;
 }