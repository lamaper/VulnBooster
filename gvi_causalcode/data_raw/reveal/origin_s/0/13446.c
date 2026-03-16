static void prplcb_roomlist_create ( PurpleRoomlist * list ) {
 struct purple_roomlist_data * rld ;
 list -> ui_data = rld = g_new0 ( struct purple_roomlist_data , 1 ) ;
 rld -> topic = - 1 ;
 }