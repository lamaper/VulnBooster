static void h245_add_label ( guint32 new_frame_num , const gchar * frame_label , const gchar * comment ) {
 h245_free_labels ( new_frame_num ) ;
 h245_labels . frame_num = new_frame_num ;
 h245_labels . labels [ h245_labels . labels_count ] . frame_label = g_strdup ( frame_label ) ;
 h245_labels . labels [ h245_labels . labels_count ] . comment = g_strdup ( comment ) ;
 if ( h245_labels . labels_count < ( H245_MAX - 1 ) ) h245_labels . labels_count ++ ;
 }