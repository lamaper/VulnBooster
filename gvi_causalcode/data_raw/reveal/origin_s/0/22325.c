static void extended_com_err_fn ( const char * myprog , errcode_t code , const char * fmt , va_list args ) {
 const char * emsg ;
 if ( code ) {
 emsg = krb5_get_error_message ( context , code ) ;
 fprintf ( stderr , "%s: %s " , myprog , emsg ) ;
 krb5_free_error_message ( context , emsg ) ;
 }
 else {
 fprintf ( stderr , "%s: " , myprog ) ;
 }
 vfprintf ( stderr , fmt , args ) ;
 fprintf ( stderr , "\n" ) ;
 }