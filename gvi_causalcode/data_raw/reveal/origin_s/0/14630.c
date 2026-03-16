static void signal_channel_destroyed ( CHANNEL_REC * channel ) {
 WINDOW_REC * window ;
 g_return_if_fail ( channel != NULL ) ;
 window = window_item_window ( ( WI_ITEM_REC * ) channel ) ;
 if ( window == NULL ) return ;
 window_item_destroy ( ( WI_ITEM_REC * ) channel ) ;
 if ( channel -> joined && ! channel -> left && ! channel -> server -> disconnected ) {
 window_bind_add ( window , channel -> server -> tag , channel -> visible_name ) ;
 }
 else if ( ! channel -> joined || channel -> left ) window_auto_destroy ( window ) ;
 }