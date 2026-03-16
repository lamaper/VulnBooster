PHP_FUNCTION ( uwsgi_cache_update ) {
 char * key = NULL ;
 int keylen ;
 char * value = NULL ;
 int vallen ;
 uint64_t expires = 0 ;
 char * cache = NULL ;
 int cachelen = 0 ;
 if ( ! uwsgi . caches ) RETURN_NULL ( ) ;
 if ( zend_parse_parameters ( ZEND_NUM_ARGS ( ) TSRMLS_CC , "ss|ls" , & key , & keylen , & value , & vallen , & expires , & cache , & cachelen ) == FAILURE ) {
 RETURN_NULL ( ) ;
 }
 if ( ! uwsgi_cache_magic_set ( key , keylen , value , vallen , expires , UWSGI_CACHE_FLAG_UPDATE , cache ) ) {
 RETURN_TRUE ;
 }
 RETURN_NULL ( ) ;
 }