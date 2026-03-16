PHP_FUNCTION ( uwsgi_masterpid ) {
 if ( uwsgi . master_process ) {
 RETURN_LONG ( uwsgi . workers [ 0 ] . pid ) ;
 }
 RETURN_LONG ( 0 ) ;
 }