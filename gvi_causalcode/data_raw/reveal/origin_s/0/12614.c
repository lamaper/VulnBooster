static void prplcb_conv_write ( PurpleConversation * conv , const char * who , const char * alias , const char * message , PurpleMessageFlags flags , time_t mtime ) {
 if ( flags & PURPLE_MESSAGE_SEND ) {
 handle_conv_msg ( conv , who , message , OPT_SELFMESSAGE , mtime ) ;
 }
 }