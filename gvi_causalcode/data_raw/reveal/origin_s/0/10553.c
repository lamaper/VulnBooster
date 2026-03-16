void prplcb_conv_del_users ( PurpleConversation * conv , GList * cbuddies ) {
 struct groupchat * gc = conv -> ui_data ;
 GList * b ;
 for ( b = cbuddies ;
 b ;
 b = b -> next ) {
 imcb_chat_remove_buddy ( gc , b -> data , "" ) ;
 }
 }