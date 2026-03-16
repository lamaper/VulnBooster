static PHP_MSHUTDOWN_FUNCTION ( zip ) {

 php_unregister_url_stream_wrapper ( "zip" TSRMLS_CC ) ;

 }