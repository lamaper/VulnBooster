static int dissect_CPMFindIndices ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * parent_tree , gboolean in , void * data _U_ ) {
 gint offset = 16 ;
 proto_item * item ;
 proto_tree * tree ;
 col_append_str ( pinfo -> cinfo , COL_INFO , "FindIndices" ) ;
 item = proto_tree_add_item ( parent_tree , hf_mswsp_msg , tvb , offset , - 1 , ENC_NA ) ;
 tree = proto_item_add_subtree ( item , ett_mswsp_msg ) ;
 proto_item_set_text ( item , "FindIndices%s" , in ? "In" : "Out" ) ;
 if ( in ) {
 guint32 cWids ;
 guint32 cDepthPrev ;
 cWids = tvb_get_letohl ( tvb , offset ) ;
 proto_tree_add_uint ( tree , hf_mswsp_msg_cpmfindindices_cwids , tvb , offset , 4 , cWids ) ;
 offset += 4 ;
 cDepthPrev = tvb_get_letohl ( tvb , offset ) ;
 proto_tree_add_uint ( tree , hf_mswsp_msg_cpmfindindices_cdepthprev , tvb , offset , 4 , cDepthPrev ) ;
 offset += 4 ;
 offset = parse_uin32_array ( tvb , offset , tree , cWids , "pwids" ) ;
 parse_uin32_array ( tvb , offset , tree , cDepthPrev , "prgiRowPrev" ) ;
 }
 else {
 guint32 cDepthNext ;
 cDepthNext = tvb_get_letohl ( tvb , offset ) ;
 proto_tree_add_uint ( tree , hf_mswsp_msg_cpmfindindices_cdepthnext , tvb , offset , 4 , cDepthNext ) ;
 offset += 4 ;
 parse_uin32_array ( tvb , offset , tree , cDepthNext , "prgiRowNext" ) ;
 }
 return tvb_reported_length ( tvb ) ;
 }