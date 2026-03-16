static int strncat_from_utf8_libarchive2 ( struct archive_string * as , const void * _p , size_t len , struct archive_string_conv * sc ) {
 const char * s ;
 int n ;
 char * p ;
 char * end ;
 uint32_t unicode ;

 memset ( & shift_state , 0 , sizeof ( shift_state ) ) ;


 if ( archive_string_ensure ( as , as -> length + len + 1 ) == NULL ) return ( - 1 ) ;
 s = ( const char * ) _p ;
 p = as -> s + as -> length ;
 end = as -> s + as -> buffer_length - MB_CUR_MAX - 1 ;
 while ( ( n = _utf8_to_unicode ( & unicode , s , len ) ) != 0 ) {
 wchar_t wc ;
 if ( p >= end ) {
 as -> length = p - as -> s ;
 if ( archive_string_ensure ( as , as -> length + len * 2 + 1 ) == NULL ) return ( - 1 ) ;
 p = as -> s + as -> length ;
 end = as -> s + as -> buffer_length - MB_CUR_MAX - 1 ;
 }
 if ( n < 0 ) {
 n *= - 1 ;
 wc = L'?' ;
 }
 else wc = ( wchar_t ) unicode ;
 s += n ;
 len -= n ;



 p += n ;
 }
 as -> length = p - as -> s ;
 as -> s [ as -> length ] = '\0' ;
 return ( 0 ) ;
 }