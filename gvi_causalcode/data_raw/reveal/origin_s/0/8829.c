PHP_FUNCTION ( uwsgi_setprocname ) {
 char * name ;
 int name_len ;
 if ( zend_parse_parameters ( ZEND_NUM_ARGS ( ) TSRMLS_CC , "s" , & name , & name_len ) == FAILURE ) {
 RETURN_NULL ( ) ;
 }
 uwsgi_set_processname ( estrndup ( name , name_len ) ) ;
 RETURN_NULL ( ) ;
 }