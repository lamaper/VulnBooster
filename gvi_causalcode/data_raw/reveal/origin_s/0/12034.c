static void prplcb_roomlist_destroy ( PurpleRoomlist * list ) {
 g_free ( list -> ui_data ) ;
 list -> ui_data = NULL ;
 }