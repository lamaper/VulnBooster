void prplcb_conv_add_users ( PurpleConversation * conv , GList * cbuddies , gboolean new_arrivals ) {
 struct groupchat * gc = conv -> ui_data ;
 GList * b ;
 for ( b = cbuddies ;
 b ;
 b = b -> next ) {
 PurpleConvChatBuddy * pcb = b -> data ;
 imcb_chat_add_buddy ( gc , pcb -> name ) ;
 }
 }