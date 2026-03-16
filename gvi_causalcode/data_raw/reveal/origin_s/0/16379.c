static void directory_count_start ( NautilusDirectory * directory , NautilusFile * file , gboolean * doing_io ) {
 DirectoryCountState * state ;
 GFile * location ;
 if ( directory -> details -> count_in_progress != NULL ) {
 * doing_io = TRUE ;
 return ;
 }
 if ( ! is_needy ( file , should_get_directory_count_now , REQUEST_DIRECTORY_COUNT ) ) {
 return ;
 }
 * doing_io = TRUE ;
 if ( ! nautilus_file_is_directory ( file ) ) {
 file -> details -> directory_count_is_up_to_date = TRUE ;
 file -> details -> directory_count_failed = FALSE ;
 file -> details -> got_directory_count = FALSE ;
 nautilus_directory_async_state_changed ( directory ) ;
 return ;
 }
 if ( ! async_job_start ( directory , "directory count" ) ) {
 return ;
 }
 state = g_new0 ( DirectoryCountState , 1 ) ;
 state -> count_file = file ;
 state -> directory = nautilus_directory_ref ( directory ) ;
 state -> cancellable = g_cancellable_new ( ) ;
 directory -> details -> count_in_progress = state ;
 location = nautilus_file_get_location ( file ) ;

 char * uri ;
 uri = g_file_get_uri ( location ) ;
 g_message ( "load_directory called to get shallow file count for %s" , uri ) ;
 g_free ( uri ) ;
 }

 g_object_unref ( location ) ;
 }