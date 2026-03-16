static void prplcb_buddy_typing ( PurpleAccount * account , const char * who , gpointer null ) {
 PurpleConversation * conv ;
 PurpleConvIm * im ;
 int state ;
 if ( ( conv = purple_find_conversation_with_account ( PURPLE_CONV_TYPE_IM , who , account ) ) == NULL ) {
 return ;
 }
 im = PURPLE_CONV_IM ( conv ) ;
 switch ( purple_conv_im_get_typing_state ( im ) ) {
 case PURPLE_TYPING : state = OPT_TYPING ;
 break ;
 case PURPLE_TYPED : state = OPT_THINKING ;
 break ;
 default : state = 0 ;
 }
 imcb_buddy_typing ( purple_ic_by_pa ( account ) , who , state ) ;
 }