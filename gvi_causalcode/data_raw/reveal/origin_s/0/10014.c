static void purple_ui_init ( ) {
 purple_connections_set_ui_ops ( & bee_conn_uiops ) ;
 purple_blist_set_ui_ops ( & bee_blist_uiops ) ;
 purple_conversations_set_ui_ops ( & bee_conv_uiops ) ;
 purple_request_set_ui_ops ( & bee_request_uiops ) ;
 purple_privacy_set_ui_ops ( & bee_privacy_uiops ) ;
 purple_roomlist_set_ui_ops ( & bee_roomlist_uiops ) ;
 purple_notify_set_ui_ops ( & bee_notify_uiops ) ;
 purple_accounts_set_ui_ops ( & bee_account_uiops ) ;
 purple_xfers_set_ui_ops ( & bee_xfer_uiops ) ;
 if ( getenv ( "BITLBEE_DEBUG" ) ) {
 purple_debug_set_ui_ops ( & bee_debug_uiops ) ;
 }
 }