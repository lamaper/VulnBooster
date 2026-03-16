static void signal_channel_created_curwin ( CHANNEL_REC * channel ) {
 g_return_if_fail ( channel != NULL ) ;
 window_item_add ( active_win , ( WI_ITEM_REC * ) channel , FALSE ) ;
 }