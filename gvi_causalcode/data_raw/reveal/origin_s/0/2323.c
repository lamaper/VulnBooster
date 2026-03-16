void nautilus_async_destroying_file ( NautilusFile * file ) {
 NautilusDirectory * directory ;
 gboolean changed ;
 GList * node , * next ;
 ReadyCallback * callback ;
 Monitor * monitor ;
 directory = file -> details -> directory ;
 changed = FALSE ;
 for ( node = directory -> details -> call_when_ready_list ;
 node != NULL ;
 node = next ) {
 next = node -> next ;
 callback = node -> data ;
 if ( callback -> file == file ) {
 if ( callback -> active ) {
 g_warning ( "destroyed file has call_when_ready pending" ) ;
 }
 remove_callback_link ( directory , node ) ;
 changed = TRUE ;
 }
 }
 for ( node = directory -> details -> monitor_list ;
 node != NULL ;
 node = next ) {
 next = node -> next ;
 monitor = node -> data ;
 if ( monitor -> file == file ) {
 g_warning ( "destroyed file still being monitored" ) ;
 remove_monitor_link ( directory , node ) ;
 changed = TRUE ;
 }
 }
 if ( directory -> details -> count_in_progress != NULL && directory -> details -> count_in_progress -> count_file == file ) {
 directory -> details -> count_in_progress -> count_file = NULL ;
 changed = TRUE ;
 }
 if ( directory -> details -> deep_count_file == file ) {
 directory -> details -> deep_count_file = NULL ;
 changed = TRUE ;
 }
 if ( directory -> details -> mime_list_in_progress != NULL && directory -> details -> mime_list_in_progress -> mime_list_file == file ) {
 directory -> details -> mime_list_in_progress -> mime_list_file = NULL ;
 changed = TRUE ;
 }
 if ( directory -> details -> get_info_file == file ) {
 directory -> details -> get_info_file = NULL ;
 changed = TRUE ;
 }
 if ( directory -> details -> link_info_read_state != NULL && directory -> details -> link_info_read_state -> file == file ) {
 directory -> details -> link_info_read_state -> file = NULL ;
 changed = TRUE ;
 }
 if ( directory -> details -> extension_info_file == file ) {
 directory -> details -> extension_info_file = NULL ;
 changed = TRUE ;
 }
 if ( directory -> details -> thumbnail_state != NULL && directory -> details -> thumbnail_state -> file == file ) {
 directory -> details -> thumbnail_state -> file = NULL ;
 changed = TRUE ;
 }
 if ( directory -> details -> mount_state != NULL && directory -> details -> mount_state -> file == file ) {
 directory -> details -> mount_state -> file = NULL ;
 changed = TRUE ;
 }
 if ( directory -> details -> filesystem_info_state != NULL && directory -> details -> filesystem_info_state -> file == file ) {
 directory -> details -> filesystem_info_state -> file = NULL ;
 changed = TRUE ;
 }
 if ( changed ) {
 nautilus_directory_async_state_changed ( directory ) ;
 }
 }