PHP_FUNCTION ( uwsgi_cache_exists ) {
 char * key = NULL ;
 int keylen = 0 ;
 char * cache = NULL ;
 int cachelen = 0 ;
 if ( zend_parse_parameters ( ZEND_NUM_ARGS ( ) TSRMLS_CC , "s|s" , & key , & keylen , & cache , & cachelen ) == FAILURE ) {
 RETURN_NULL ( ) ;
 }
 if ( uwsgi_cache_magic_exists ( key , keylen , cache ) ) {
 RETURN_TRUE ;
 }
 RETURN_NULL ( ) ;
 }