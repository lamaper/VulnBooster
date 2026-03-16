static GList * purple_away_states ( struct im_connection * ic ) {
 struct purple_data * pd = ic -> proto_data ;
 GList * st , * ret = NULL ;
 for ( st = purple_account_get_status_types ( pd -> account ) ;
 st ;
 st = st -> next ) {
 PurpleStatusPrimitive prim = purple_status_type_get_primitive ( st -> data ) ;
 if ( prim != PURPLE_STATUS_AVAILABLE && prim != PURPLE_STATUS_OFFLINE ) {
 ret = g_list_append ( ret , ( void * ) purple_status_type_get_name ( st -> data ) ) ;
 }
 }
 return ret ;
 }