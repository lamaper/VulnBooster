void h245_add_to_graph ( guint32 new_frame_num ) {
 gint8 n ;
 if ( new_frame_num != h245_labels . frame_num ) return ;
 for ( n = 0 ;
 n < h245_labels . labels_count ;
 n ++ ) {
 append_to_frame_graph ( & the_tapinfo_struct , new_frame_num , h245_labels . labels [ n ] . frame_label , h245_labels . labels [ n ] . comment ) ;
 g_free ( h245_labels . labels [ n ] . frame_label ) ;
 h245_labels . labels [ n ] . frame_label = NULL ;
 g_free ( h245_labels . labels [ n ] . comment ) ;
 h245_labels . labels [ n ] . comment = NULL ;
 }
 h245_labels . frame_num = 0 ;
 h245_labels . labels_count = 0 ;
 }