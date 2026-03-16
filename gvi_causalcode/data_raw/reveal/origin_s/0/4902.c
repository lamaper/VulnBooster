int quit ( ) {
 kadm5_ret_t retval ;
 if ( locked ) {
 retval = kadm5_unlock ( handle ) ;
 if ( retval ) {
 com_err ( "quit" , retval , _ ( "while unlocking locked database" ) ) ;
 return 1 ;
 }
 locked = 0 ;
 }
 kadm5_destroy ( handle ) ;
 if ( ccache_name != NULL ) {
 fprintf ( stderr , "\n\a\a\a%s" , _ ( "Administration credentials NOT DESTROYED.\n" ) ) ;
 }
 krb5_klog_close ( context ) ;
 krb5_free_context ( context ) ;
 return 0 ;
 }