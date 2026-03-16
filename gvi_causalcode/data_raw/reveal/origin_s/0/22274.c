static void signal_channel_created ( CHANNEL_REC * channel , void * automatic ) {
 if ( window_item_window ( channel ) == NULL ) {
 window_item_create ( ( WI_ITEM_REC * ) channel , GPOINTER_TO_INT ( automatic ) ) ;
 }
 }