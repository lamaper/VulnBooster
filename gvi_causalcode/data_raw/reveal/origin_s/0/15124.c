static int strncat_from_utf8_to_utf8 ( struct archive_string * as , const void * _p , size_t len , struct archive_string_conv * sc ) {
 const char * s ;
 char * p , * endp ;
 int n , ret = 0 ;
 ( void ) sc ;
 if ( archive_string_ensure ( as , as -> length + len + 1 ) == NULL ) return ( - 1 ) ;
 s = ( const char * ) _p ;
 p = as -> s + as -> length ;
 endp = as -> s + as -> buffer_length - 1 ;
 do {
 uint32_t uc ;
 const char * ss = s ;
 size_t w ;
 while ( ( n = utf8_to_unicode ( & uc , s , len ) ) > 0 ) {
 s += n ;
 len -= n ;
 }
 if ( ss < s ) {
 if ( p + ( s - ss ) > endp ) {
 as -> length = p - as -> s ;
 if ( archive_string_ensure ( as , as -> buffer_length + len + 1 ) == NULL ) return ( - 1 ) ;
 p = as -> s + as -> length ;
 endp = as -> s + as -> buffer_length - 1 ;
 }
 memcpy ( p , ss , s - ss ) ;
 p += s - ss ;
 }
 if ( n < 0 ) {
 if ( n == - 3 && IS_SURROGATE_PAIR_LA ( uc ) ) {
 n = cesu8_to_unicode ( & uc , s , len ) ;
 }
 if ( n < 0 ) {
 ret = - 1 ;
 n *= - 1 ;
 }
 while ( ( w = unicode_to_utf8 ( p , endp - p , uc ) ) == 0 ) {
 as -> length = p - as -> s ;
 if ( archive_string_ensure ( as , as -> buffer_length + len + 1 ) == NULL ) return ( - 1 ) ;
 p = as -> s + as -> length ;
 endp = as -> s + as -> buffer_length - 1 ;
 }
 p += w ;
 s += n ;
 len -= n ;
 }
 }
 while ( n > 0 ) ;
 as -> length = p - as -> s ;
 as -> s [ as -> length ] = '\0' ;
 return ( ret ) ;
 }