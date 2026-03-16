static int purple_buddy_msg ( struct im_connection * ic , char * who , char * message , int flags ) {
 PurpleConversation * conv ;
 struct purple_data * pd = ic -> proto_data ;
 if ( ! strncmp ( who , PURPLE_REQUEST_HANDLE , sizeof ( PURPLE_REQUEST_HANDLE ) - 1 ) ) {
 guint request_id = atoi ( who + sizeof ( PURPLE_REQUEST_HANDLE ) ) ;
 purple_request_input_callback ( request_id , ic , message , who ) ;
 return 1 ;
 }
 if ( ( conv = purple_find_conversation_with_account ( PURPLE_CONV_TYPE_IM , who , pd -> account ) ) == NULL ) {
 conv = purple_conversation_new ( PURPLE_CONV_TYPE_IM , pd -> account , who ) ;
 }
 purple_conv_im_send ( purple_conversation_get_im_data ( conv ) , message ) ;
 return 1 ;
 }