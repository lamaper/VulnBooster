static int invalid_mbs ( const void * _p , size_t n , struct archive_string_conv * sc ) {
 const char * p = ( const char * ) _p ;
 size_t r ;

 memset ( & shift_state , 0 , sizeof ( shift_state ) ) ;


 wchar_t wc ;



 if ( r == 0 ) break ;
 p += r ;
 n -= r ;
 }
 ( void ) sc ;
 return ( 0 ) ;
 }