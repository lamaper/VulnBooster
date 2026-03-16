static void handle_conv_msg ( PurpleConversation * conv , const char * who , const char * message_ , guint32 bee_flags , time_t mtime ) {
 struct im_connection * ic = purple_ic_by_pa ( conv -> account ) ;
 struct groupchat * gc = conv -> ui_data ;
 char * message = g_strdup ( message_ ) ;
 PurpleBuddy * buddy ;
 buddy = purple_find_buddy ( conv -> account , who ) ;
 if ( buddy != NULL ) {
 who = purple_buddy_get_name ( buddy ) ;
 }
 if ( conv -> type == PURPLE_CONV_TYPE_IM ) {
 imcb_buddy_msg ( ic , who , message , bee_flags , mtime ) ;
 }
 else if ( gc ) {
 imcb_chat_msg ( gc , who , message , bee_flags , mtime ) ;
 }
 g_free ( message ) ;
 }