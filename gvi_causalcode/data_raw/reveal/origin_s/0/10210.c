PHP_FUNCTION ( uwsgi_signal ) {
 long long_signum ;
 uint8_t signum = 0 ;
 if ( zend_parse_parameters ( ZEND_NUM_ARGS ( ) TSRMLS_CC , "l" , & long_signum ) == FAILURE ) {
 RETURN_NULL ( ) ;
 }
 signum = ( uint8_t ) long_signum ;
 uwsgi_signal_send ( uwsgi . signal_socket , signum ) ;
 RETURN_NULL ( ) ;
 }