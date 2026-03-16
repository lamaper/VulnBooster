static gboolean check_for_offset ( proto_node * node , gpointer data ) {
 field_info * fi = PNODE_FINFO ( node ) ;
 offset_search_t * offsearch = ( offset_search_t * ) data ;
 if ( fi && ! PROTO_ITEM_IS_HIDDEN ( node ) && ! PROTO_ITEM_IS_GENERATED ( node ) && fi -> ds_tvb && offsearch -> tvb == fi -> ds_tvb ) {
 if ( offsearch -> offset >= ( guint ) fi -> start && offsearch -> offset < ( guint ) ( fi -> start + fi -> length ) ) {
 offsearch -> finfo = fi ;
 return FALSE ;
 }
 }
 return FALSE ;
 }