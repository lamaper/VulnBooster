static void signal_window_item_changed ( WINDOW_REC * window , WI_ITEM_REC * item ) {
 g_return_if_fail ( window != NULL ) ;
 if ( item == NULL ) return ;
 if ( g_slist_length ( window -> items ) > 1 && IS_CHANNEL ( item ) ) {
 printformat ( item -> server , item -> visible_name , MSGLEVEL_CLIENTNOTICE , TXT_TALKING_IN , item -> visible_name ) ;
 signal_stop ( ) ;
 }
 }