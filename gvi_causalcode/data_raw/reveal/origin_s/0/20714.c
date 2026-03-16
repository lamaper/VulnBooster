void prplcb_conv_free ( PurpleConversation * conv ) {
 struct groupchat * gc = conv -> ui_data ;
 imcb_chat_free ( gc ) ;
 }