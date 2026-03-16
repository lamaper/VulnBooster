void prplcb_conv_new ( PurpleConversation * conv ) {
 if ( conv -> type == PURPLE_CONV_TYPE_CHAT ) {
 struct im_connection * ic = purple_ic_by_pa ( conv -> account ) ;
 struct groupchat * gc ;
 gc = bee_chat_by_title ( ic -> bee , ic , conv -> name ) ;
 if ( ! gc ) {
 gc = imcb_chat_new ( ic , conv -> name ) ;
 if ( conv -> title != NULL ) {
 imcb_chat_name_hint ( gc , conv -> title ) ;
 }
 }
 if ( conv -> title != NULL && strcmp ( conv -> name , conv -> title ) != 0 ) {
 imcb_chat_topic ( gc , NULL , conv -> title , 0 ) ;
 }
 conv -> ui_data = gc ;
 gc -> data = conv ;
 imcb_chat_add_buddy ( gc , gc -> ic -> acc -> user ) ;
 }
 }