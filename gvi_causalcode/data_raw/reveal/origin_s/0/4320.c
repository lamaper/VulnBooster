void * prplcb_request_input ( const char * title , const char * primary , const char * secondary , const char * default_value , gboolean multiline , gboolean masked , gchar * hint , const char * ok_text , GCallback ok_cb , const char * cancel_text , GCallback cancel_cb , PurpleAccount * account , const char * who , PurpleConversation * conv , void * user_data ) {
 struct im_connection * ic = purple_ic_by_pa ( account ) ;
 struct purple_data * pd = ic -> proto_data ;
 struct request_input_data * ri ;
 guint id ;
 if ( pd -> chat_list_server && title && g_strcmp0 ( title , "Enter a Conference Server" ) == 0 ) {
 ( ( ri_callback_t ) ok_cb ) ( user_data , pd -> chat_list_server ) ;
 g_free ( pd -> chat_list_server ) ;
 pd -> chat_list_server = NULL ;
 return NULL ;
 }
 id = pd -> next_request_id ++ ;
 ri = g_new0 ( struct request_input_data , 1 ) ;
 ri -> id = id ;
 ri -> ic = ic ;
 ri -> buddy = g_strdup_printf ( "%s_%u" , PURPLE_REQUEST_HANDLE , id ) ;
 ri -> data_callback = ( ri_callback_t ) ok_cb ;
 ri -> user_data = user_data ;
 g_hash_table_insert ( pd -> input_requests , GUINT_TO_POINTER ( id ) , ri ) ;
 imcb_add_buddy ( ic , ri -> buddy , NULL ) ;
 if ( title && * title ) {
 imcb_buddy_msg ( ic , ri -> buddy , title , 0 , 0 ) ;
 }
 if ( primary && * primary ) {
 imcb_buddy_msg ( ic , ri -> buddy , primary , 0 , 0 ) ;
 }
 if ( secondary && * secondary ) {
 imcb_buddy_msg ( ic , ri -> buddy , secondary , 0 , 0 ) ;
 }
 return ri ;
 }