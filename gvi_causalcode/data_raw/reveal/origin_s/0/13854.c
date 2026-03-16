static gint nlm_msg_res_matched_equal ( gconstpointer k1 , gconstpointer k2 ) {
 guint mk1 = GPOINTER_TO_UINT ( k1 ) ;
 guint mk2 = GPOINTER_TO_UINT ( k2 ) ;
 return ( mk1 == mk2 ) ;
 }