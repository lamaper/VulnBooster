static int purple_send_typing ( struct im_connection * ic , char * who , int flags ) {
 PurpleTypingState state = PURPLE_NOT_TYPING ;
 struct purple_data * pd = ic -> proto_data ;
 if ( flags & OPT_TYPING ) {
 state = PURPLE_TYPING ;
 }
 else if ( flags & OPT_THINKING ) {
 state = PURPLE_TYPED ;
 }
 serv_send_typing ( purple_account_get_connection ( pd -> account ) , who , state ) ;
 return 1 ;
 }