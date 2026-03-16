static int dissect_CPMGetScopeStatistics ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * parent_tree , gboolean in , void * data _U_ ) {
 gint offset = 16 ;
 proto_item * item ;
 proto_tree * tree ;
 item = proto_tree_add_item ( parent_tree , hf_mswsp_msg , tvb , offset , in ? 0 : - 1 , ENC_NA ) ;
 tree = proto_item_add_subtree ( item , ett_mswsp_msg ) ;
 proto_item_set_text ( item , "GetScopeStatistics%s" , in ? "In" : "Out" ) ;
 col_append_str ( pinfo -> cinfo , COL_INFO , "GetScopeStatistics" ) ;
 if ( in ) {
 }
 else {
 proto_tree_add_item ( tree , hf_mswsp_msg_cpmsetscopestatisics_dwindexitems , tvb , offset , 4 , ENC_LITTLE_ENDIAN ) ;
 offset += 4 ;
 proto_tree_add_item ( tree , hf_mswsp_msg_cpmsetscopestatisics_dwoutstandingadds , tvb , offset , 4 , ENC_LITTLE_ENDIAN ) ;
 offset += 4 ;
 proto_tree_add_item ( tree , hf_mswsp_msg_cpmsetscopestatisics_dwoutstandingmodifies , tvb , offset , 4 , ENC_LITTLE_ENDIAN ) ;
 }
 return tvb_reported_length ( tvb ) ;
 }