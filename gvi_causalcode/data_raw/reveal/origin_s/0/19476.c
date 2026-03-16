static int dissect_mac_fdd_edch ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , void * data ) {
 proto_tree * edch_tree = NULL ;
 proto_item * channel_type ;
 umts_mac_info * macinf ;
 fp_info * fpinf ;
 guint16 pos ;
 proto_item * ti = NULL ;
 col_set_str ( pinfo -> cinfo , COL_PROTOCOL , "MAC" ) ;
 ti = proto_tree_add_item ( tree , proto_umts_mac , tvb , 0 , - 1 , ENC_NA ) ;
 edch_tree = proto_item_add_subtree ( ti , ett_mac_edch ) ;
 fpinf = ( fp_info * ) p_get_proto_data ( wmem_file_scope ( ) , pinfo , proto_fp , 0 ) ;
 macinf = ( umts_mac_info * ) p_get_proto_data ( wmem_file_scope ( ) , pinfo , proto_umts_mac , 0 ) ;
 if ( ! macinf || ! fpinf ) {
 proto_tree_add_expert ( edch_tree , pinfo , & ei_mac_per_frame_info_missing , tvb , 0 , - 1 ) ;
 return 1 ;
 }
 pos = fpinf -> cur_tb ;
 switch ( macinf -> content [ pos ] ) {
 case MAC_CONTENT_DCCH : proto_item_append_text ( ti , " (DCCH)" ) ;
 channel_type = proto_tree_add_uint ( edch_tree , hf_mac_lch_id , tvb , 0 , 0 , macinf -> lchid [ pos ] ) ;
 PROTO_ITEM_SET_GENERATED ( channel_type ) ;
 channel_type = proto_tree_add_uint ( edch_tree , hf_mac_channel , tvb , 0 , 0 , MAC_DCCH ) ;
 PROTO_ITEM_SET_GENERATED ( channel_type ) ;
 call_dissector_with_data ( rlc_dcch_handle , tvb , pinfo , tree , data ) ;
 break ;
 case MAC_CONTENT_PS_DTCH : proto_item_append_text ( ti , " (PS DTCH)" ) ;
 channel_type = proto_tree_add_uint ( edch_tree , hf_mac_lch_id , tvb , 0 , 0 , macinf -> lchid [ pos ] ) ;
 PROTO_ITEM_SET_GENERATED ( channel_type ) ;
 channel_type = proto_tree_add_uint ( edch_tree , hf_mac_channel , tvb , 0 , 0 , MAC_DTCH ) ;
 PROTO_ITEM_SET_GENERATED ( channel_type ) ;
 call_dissector_with_data ( rlc_ps_dtch_handle , tvb , pinfo , tree , data ) ;
 break ;
 case MAC_CONTENT_CS_DTCH : proto_item_append_text ( ti , " (CS DTCH)" ) ;
 break ;
 default : proto_item_append_text ( ti , " (Unknown EDCH Content)" ) ;
 expert_add_info_format ( pinfo , ti , & ei_mac_unknown_content , "Unknown EDCH Content" ) ;
 break ;
 }
 return tvb_captured_length ( tvb ) ;
 }