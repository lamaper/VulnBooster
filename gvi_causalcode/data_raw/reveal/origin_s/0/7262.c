PHP_FUNCTION ( uwsgi_cache_clear ) {
 char * cache = NULL ;
 int cachelen = 0 ;
 if ( zend_parse_parameters ( ZEND_NUM_ARGS ( ) TSRMLS_CC , "|s" , & cache , & cachelen ) == FAILURE ) {
 RETURN_NULL ( ) ;
 }
 if ( ! uwsgi_cache_magic_clear ( cache ) ) {
 RETURN_TRUE ;
 }
 RETURN_NULL ( ) ;
 }