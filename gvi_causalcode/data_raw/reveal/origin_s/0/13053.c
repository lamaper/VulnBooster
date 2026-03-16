static void prplcb_conv_msg ( PurpleConversation * conv , const char * who , const char * message , PurpleMessageFlags flags , time_t mtime ) {
 if ( ! ( flags & PURPLE_MESSAGE_SEND ) ) {
 handle_conv_msg ( conv , who , message , 0 , mtime ) ;
 }
 }