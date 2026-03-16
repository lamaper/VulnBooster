static guint change_call_num_graph ( voip_calls_tapinfo_t * tapinfo _U_ , guint16 call_num , guint16 new_call_num ) {
 seq_analysis_item_t * gai ;
 GList * list ;
 guint items_changed ;
 items_changed = 0 ;
 list = g_list_first ( tapinfo -> graph_analysis -> list ) ;
 while ( list ) {
 gai = ( seq_analysis_item_t * ) list -> data ;
 if ( gai -> conv_num == call_num ) {
 gai -> conv_num = new_call_num ;
 items_changed ++ ;
 }
 list = g_list_next ( list ) ;
 }
 return items_changed ;
 }