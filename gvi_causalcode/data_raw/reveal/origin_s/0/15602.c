static gboolean pk_transaction_set_hint ( PkTransaction * transaction , const gchar * key , const gchar * value , GError * * error ) {
 PkTransactionPrivate * priv = transaction -> priv ;
 if ( g_strcmp0 ( key , "locale" ) == 0 ) {
 pk_backend_job_set_locale ( priv -> job , value ) ;
 return TRUE ;
 }
 if ( g_strcmp0 ( key , "frontend-socket" ) == 0 ) {
 if ( value == NULL || value [ 0 ] == '\0' ) {
 g_set_error_literal ( error , PK_TRANSACTION_ERROR , PK_TRANSACTION_ERROR_NOT_SUPPORTED , "Could not set frontend-socket to nothing" ) ;
 return FALSE ;
 }
 if ( value [ 0 ] != '/' ) {
 g_set_error_literal ( error , PK_TRANSACTION_ERROR , PK_TRANSACTION_ERROR_NOT_SUPPORTED , "frontend-socket has to be an absolute path" ) ;
 return FALSE ;
 }
 if ( ! g_file_test ( value , G_FILE_TEST_EXISTS ) ) {
 g_set_error_literal ( error , PK_TRANSACTION_ERROR , PK_TRANSACTION_ERROR_NOT_SUPPORTED , "frontend-socket does not exist" ) ;
 return FALSE ;
 }
 pk_backend_job_set_frontend_socket ( priv -> job , value ) ;
 return TRUE ;
 }
 if ( g_strcmp0 ( key , "background" ) == 0 ) {
 if ( g_strcmp0 ( value , "true" ) == 0 ) {
 pk_backend_job_set_background ( priv -> job , TRUE ) ;
 }
 else if ( g_strcmp0 ( value , "false" ) == 0 ) {
 pk_backend_job_set_background ( priv -> job , FALSE ) ;
 }
 else {
 g_set_error ( error , PK_TRANSACTION_ERROR , PK_TRANSACTION_ERROR_NOT_SUPPORTED , "background hint expects true or false, not %s" , value ) ;
 return FALSE ;
 }
 return TRUE ;
 }
 if ( g_strcmp0 ( key , "interactive" ) == 0 ) {
 if ( g_strcmp0 ( value , "true" ) == 0 ) {
 pk_backend_job_set_interactive ( priv -> job , TRUE ) ;
 }
 else if ( g_strcmp0 ( value , "false" ) == 0 ) {
 pk_backend_job_set_interactive ( priv -> job , FALSE ) ;
 }
 else {
 g_set_error ( error , PK_TRANSACTION_ERROR , PK_TRANSACTION_ERROR_NOT_SUPPORTED , "interactive hint expects true or false, not %s" , value ) ;
 return FALSE ;
 }
 return TRUE ;
 }
 if ( g_strcmp0 ( key , "cache-age" ) == 0 ) {
 guint cache_age ;
 if ( ! pk_strtouint ( value , & cache_age ) ) {
 g_set_error ( error , PK_TRANSACTION_ERROR , PK_TRANSACTION_ERROR_NOT_SUPPORTED , "cannot parse cache age value %s" , value ) ;
 return FALSE ;
 }
 if ( cache_age == 0 ) {
 g_set_error_literal ( error , PK_TRANSACTION_ERROR , PK_TRANSACTION_ERROR_NOT_SUPPORTED , "cannot set a cache age of zero" ) ;
 return FALSE ;
 }
 pk_backend_job_set_cache_age ( priv -> job , cache_age ) ;
 return TRUE ;
 }
 g_warning ( "unknown option: %s with value %s" , key , value ) ;
 return TRUE ;
 }