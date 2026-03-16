static int dissect_mac_fdd_pch ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , void * data ) {
 proto_tree * pch_tree = NULL ;
 proto_item * channel_type ;
 col_set_str ( pinfo -> cinfo , COL_PROTOCOL , "MAC" ) ;
 col_set_str ( pinfo -> cinfo , COL_INFO , "PCCH" ) ;
 if ( tree ) {
 proto_item * ti ;
 ti = proto_tree_add_item ( tree , proto_umts_mac , tvb , 0 , - 1 , ENC_NA ) ;
 pch_tree = proto_item_add_subtree ( ti , ett_mac_pch ) ;
 proto_item_append_text ( ti , " (PCCH)" ) ;
 channel_type = proto_tree_add_uint ( pch_tree , hf_mac_channel , tvb , 0 , 0 , MAC_PCCH ) ;
 PROTO_ITEM_SET_GENERATED ( channel_type ) ;
 }
 call_dissector_with_data ( rlc_pcch_handle , tvb , pinfo , tree , data ) ;
 return tvb_captured_length ( tvb ) ;
 }