static void * prplcb_account_request_authorize ( PurpleAccount * account , const char * remote_user , const char * id , const char * alias , const char * message , gboolean on_list , PurpleAccountRequestAuthorizationCb authorize_cb , PurpleAccountRequestAuthorizationCb deny_cb , void * user_data ) {
 struct im_connection * ic = purple_ic_by_pa ( account ) ;
 char * q ;
 if ( alias ) {
 q = g_strdup_printf ( "%s (%s) wants to add you to his/her contact " "list. (%s)" , alias , remote_user , message ) ;
 }
 else {
 q = g_strdup_printf ( "%s wants to add you to his/her contact " "list. (%s)" , remote_user , message ) ;
 }
 imcb_ask_with_free ( ic , q , user_data , authorize_cb , deny_cb , NULL ) ;
 g_free ( q ) ;
 return NULL ;
 }