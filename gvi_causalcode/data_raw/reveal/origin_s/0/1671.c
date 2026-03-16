static int dissect_CPMFetchValue ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * parent_tree , gboolean in , void * data _U_ ) {
 gint offset = 16 ;
 proto_item * item ;
 proto_tree * tree , * pad_tree ;
 col_append_str ( pinfo -> cinfo , COL_INFO , "FetchValue" ) ;
 item = proto_tree_add_item ( parent_tree , hf_mswsp_msg , tvb , offset , - 1 , ENC_NA ) ;
 tree = proto_tree_add_subtree_format ( parent_tree , tvb , offset , 0 , ett_mswsp_msg , & item , "FetchValue%s" , in ? "In" : "Out" ) ;
 pad_tree = proto_tree_add_subtree ( tree , tvb , offset , 0 , ett_mswsp_pad , NULL , "Padding" ) ;
 if ( in ) {
 struct CFullPropSpec prop ;
 proto_tree_add_item ( tree , hf_mswsp_msg_cpmfetchvalue_wid , tvb , offset , 4 , ENC_LITTLE_ENDIAN ) ;
 offset += 4 ;
 proto_tree_add_item ( tree , hf_mswsp_msg_cpmfetchvalue_cbsofar , tvb , offset , 4 , ENC_LITTLE_ENDIAN ) ;
 offset += 4 ;
 proto_tree_add_item ( tree , hf_mswsp_msg_cpmfetchvalue_cbpropspec , tvb , offset , 4 , ENC_LITTLE_ENDIAN ) ;
 offset += 4 ;
 proto_tree_add_item ( tree , hf_mswsp_msg_cpmfetchvalue_cbchunk , tvb , offset , 4 , ENC_LITTLE_ENDIAN ) ;
 offset += 4 ;
 offset = parse_CFullPropSpec ( tvb , offset , tree , pad_tree , & prop , "PropSpec" ) ;
 parse_padding ( tvb , offset , 4 , pad_tree , "_padding" ) ;
 }
 else {
 guint32 cbValue = tvb_get_letohl ( tvb , offset ) ;
 proto_tree_add_item ( tree , hf_mswsp_msg_cpmfetchvalue_cbvalue , tvb , offset , 4 , ENC_LITTLE_ENDIAN ) ;
 offset += 4 ;
 proto_tree_add_item ( tree , hf_mswsp_msg_cpmfetchvalue_fmoreexists , tvb , offset , 4 , ENC_LITTLE_ENDIAN ) ;
 offset += 4 ;
 proto_tree_add_item ( tree , hf_mswsp_msg_cpmfetchvalue_fvalueexists , tvb , offset , 4 , ENC_LITTLE_ENDIAN ) ;
 offset += 4 ;
 proto_tree_add_item ( tree , hf_mswsp_msg_cpmfetchvalue_vvalue , tvb , offset , cbValue , ENC_NA ) ;
 }
 return tvb_reported_length ( tvb ) ;
 }