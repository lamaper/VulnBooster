static void prplcb_roomlist_set_fields ( PurpleRoomlist * list , GList * fields ) {
 gint topic = - 1 ;
 GList * l ;
 guint i ;
 PurpleRoomlistField * field ;
 struct purple_roomlist_data * rld = list -> ui_data ;
 for ( i = 0 , l = fields ;
 l ;
 i ++ , l = l -> next ) {
 field = l -> data ;
 if ( i != 0 && topic < 0 && ! field -> hidden && field -> type == PURPLE_ROOMLIST_FIELD_STRING ) {
 topic = i ;
 }
 if ( ( g_strcasecmp ( field -> name , "description" ) == 0 ) || ( g_strcasecmp ( field -> name , "topic" ) == 0 ) ) {
 if ( field -> type == PURPLE_ROOMLIST_FIELD_STRING ) {
 rld -> topic = i ;
 }
 }
 }
 if ( rld -> topic < 0 ) {
 rld -> topic = topic ;
 }
 }