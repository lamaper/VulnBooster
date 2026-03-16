static int append_to_frame_graph ( voip_calls_tapinfo_t * tapinfo _U_ , guint32 frame_num , const gchar * new_frame_label , const gchar * new_comment ) {
 seq_analysis_item_t * gai = NULL ;
 gchar * frame_label = NULL ;
 gchar * comment = NULL ;
 if ( NULL != tapinfo -> graph_analysis -> ht ) gai = ( seq_analysis_item_t * ) g_hash_table_lookup ( tapinfo -> graph_analysis -> ht , & frame_num ) ;
 if ( gai ) {
 frame_label = gai -> frame_label ;
 comment = gai -> comment ;
 if ( new_frame_label != NULL ) {
 gai -> frame_label = g_strdup_printf ( "%s %s" , frame_label , new_frame_label ) ;
 g_free ( frame_label ) ;
 }
 if ( new_comment != NULL ) {
 gai -> comment = g_strdup_printf ( "%s %s" , comment , new_comment ) ;
 g_free ( comment ) ;
 }
 }
 return gai ? 1 : 0 ;
 }