PHP_FUNCTION ( uwsgi_rpc ) {
 int num_args = 0 ;
 int i ;
 char * node = NULL ;
 char * func = NULL ;
 zval * * * varargs = NULL ;
 zval * z_current_obj ;
 char * argv [ 256 ] ;
 uint16_t argvs [ 256 ] ;
 uint64_t size = 0 ;
 if ( zend_parse_parameters ( ZEND_NUM_ARGS ( ) TSRMLS_CC , "+" , & varargs , & num_args ) == FAILURE ) {
 RETURN_NULL ( ) ;
 }
 if ( num_args < 2 ) goto clear ;
 if ( num_args > 256 + 2 ) goto clear ;
 z_current_obj = * varargs [ 0 ] ;
 if ( Z_TYPE_P ( z_current_obj ) != IS_STRING ) {
 goto clear ;
 }
 node = Z_STRVAL_P ( z_current_obj ) ;
 z_current_obj = * varargs [ 1 ] ;
 if ( Z_TYPE_P ( z_current_obj ) != IS_STRING ) {
 goto clear ;
 }
 func = Z_STRVAL_P ( z_current_obj ) ;
 for ( i = 0 ;
 i < ( num_args - 2 ) ;
 i ++ ) {
 z_current_obj = * varargs [ i + 2 ] ;
 if ( Z_TYPE_P ( z_current_obj ) != IS_STRING ) {
 goto clear ;
 }
 argv [ i ] = Z_STRVAL_P ( z_current_obj ) ;
 argvs [ i ] = Z_STRLEN_P ( z_current_obj ) ;
 }
 char * response = uwsgi_do_rpc ( node , func , num_args - 2 , argv , argvs , & size ) ;
 if ( response ) {
 char * ret = estrndup ( response , size ) ;
 free ( response ) ;



 clear : efree ( varargs ) ;
 RETURN_NULL ( ) ;
 }