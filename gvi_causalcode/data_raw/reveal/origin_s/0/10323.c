static void purple_set_away ( struct im_connection * ic , char * state_txt , char * message ) {
 struct purple_data * pd = ic -> proto_data ;
 GList * status_types = purple_account_get_status_types ( pd -> account ) , * st ;
 PurpleStatusType * pst = NULL ;
 GList * args = NULL ;
 for ( st = status_types ;
 st ;
 st = st -> next ) {
 pst = st -> data ;
 if ( state_txt == NULL && purple_status_type_get_primitive ( pst ) == PURPLE_STATUS_AVAILABLE ) {
 break ;
 }
 if ( state_txt != NULL && g_strcasecmp ( state_txt , purple_status_type_get_name ( pst ) ) == 0 ) {
 break ;
 }
 }
 if ( message && purple_status_type_get_attr ( pst , "message" ) ) {
 args = g_list_append ( args , "message" ) ;
 args = g_list_append ( args , message ) ;
 }
 purple_account_set_status_list ( pd -> account , st ? purple_status_type_get_id ( pst ) : "away" , TRUE , args ) ;
 g_list_free ( args ) ;
 }