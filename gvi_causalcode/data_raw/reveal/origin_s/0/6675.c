static void sig_disconnected ( SERVER_REC * server ) {
 WINDOW_REC * window ;
 GSList * tmp ;
 g_return_if_fail ( IS_SERVER ( server ) ) ;
 for ( tmp = server -> channels ;
 tmp != NULL ;
 tmp = tmp -> next ) {
 CHANNEL_REC * channel = tmp -> data ;
 window = window_item_window ( ( WI_ITEM_REC * ) channel ) ;
 window_bind_add ( window , server -> tag , channel -> name ) ;
 }
 }