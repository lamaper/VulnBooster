static int dissect_mac_fdd_hsdsch ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , void * data ) {
 proto_tree * hsdsch_tree = NULL ;
 proto_item * channel_type ;
 fp_info * fpinf ;
 umts_mac_info * macinf ;
 guint16 pos ;
 guint8 bitoffs = 0 ;
 tvbuff_t * next_tvb ;
 proto_item * ti = NULL ;
 rlc_info * rlcinf ;
 col_set_str ( pinfo -> cinfo , COL_PROTOCOL , "MAC" ) ;
 ti = proto_tree_add_item ( tree , proto_umts_mac , tvb , 0 , - 1 , ENC_NA ) ;
 hsdsch_tree = proto_item_add_subtree ( ti , ett_mac_hsdsch ) ;
 fpinf = ( fp_info * ) p_get_proto_data ( wmem_file_scope ( ) , pinfo , proto_fp , 0 ) ;
 macinf = ( umts_mac_info * ) p_get_proto_data ( wmem_file_scope ( ) , pinfo , proto_umts_mac , 0 ) ;
 pos = fpinf -> cur_tb ;
 bitoffs = fpinf -> hsdsch_entity == ehs ? 0 : 4 ;
 if ( ! macinf ) {
 proto_tree_add_expert ( hsdsch_tree , pinfo , & ei_mac_per_frame_info_missing , tvb , 0 , - 1 ) ;
 return 1 ;
 }
 if ( macinf -> ctmux [ pos ] ) {
 proto_tree_add_bits_item ( hsdsch_tree , hf_mac_ct , tvb , bitoffs , 4 , ENC_BIG_ENDIAN ) ;
 macinf -> lchid [ pos ] = tvb_get_bits8 ( tvb , bitoffs , 4 ) + 1 ;
 macinf -> fake_chid [ pos ] = FALSE ;
 macinf -> content [ pos ] = lchId_type_table [ macinf -> lchid [ pos ] ] ;
 rlcinf = ( rlc_info * ) p_get_proto_data ( wmem_file_scope ( ) , pinfo , proto_rlc , 0 ) ;
 rlcinf -> rbid [ pos ] = macinf -> lchid [ pos ] ;
 rlcinf -> mode [ pos ] = lchId_rlc_map [ macinf -> lchid [ pos ] ] ;
 bitoffs += 4 ;
 }
 if ( ( bitoffs % 8 ) == 0 ) {
 next_tvb = tvb_new_subset_remaining ( tvb , bitoffs / 8 ) ;
 }
 else {
 next_tvb = tvb_new_octet_aligned ( tvb , bitoffs , macinf -> pdu_len ) ;
 add_new_data_source ( pinfo , next_tvb , "Octet-Aligned HSDSCH Data" ) ;
 }
 switch ( macinf -> content [ pos ] ) {
 case MAC_CONTENT_CCCH : proto_item_append_text ( ti , " (CCCH)" ) ;
 channel_type = proto_tree_add_uint ( hsdsch_tree , hf_mac_lch_id , tvb , 0 , 0 , macinf -> lchid [ pos ] ) ;
 PROTO_ITEM_SET_GENERATED ( channel_type ) ;
 if ( macinf -> lchid [ pos ] != 255 ) {
 if ( macinf -> fake_chid [ pos ] ) {
 expert_add_info ( pinfo , channel_type , & ei_mac_faked_logical_channel_id ) ;
 }
 }
 else {
 expert_add_info ( pinfo , channel_type , & ei_mac_no_logical_channel ) ;
 }
 channel_type = proto_tree_add_uint ( hsdsch_tree , hf_mac_channel , tvb , 0 , 0 , MAC_DCCH ) ;
 PROTO_ITEM_SET_GENERATED ( channel_type ) ;
 channel_type = proto_tree_add_uint ( hsdsch_tree , hf_mac_macdflowd_id , tvb , 0 , 0 , macinf -> macdflow_id [ pos ] ) ;
 PROTO_ITEM_SET_GENERATED ( channel_type ) ;
 call_dissector_with_data ( rlc_ccch_handle , next_tvb , pinfo , tree , data ) ;
 break ;
 case MAC_CONTENT_DCCH : proto_item_append_text ( ti , " (DCCH)" ) ;
 channel_type = proto_tree_add_uint ( hsdsch_tree , hf_mac_lch_id , tvb , 0 , 0 , macinf -> lchid [ pos ] ) ;
 PROTO_ITEM_SET_GENERATED ( channel_type ) ;
 if ( macinf -> lchid [ pos ] != 255 ) {
 if ( macinf -> fake_chid [ pos ] ) {
 expert_add_info ( pinfo , channel_type , & ei_mac_faked_logical_channel_id ) ;
 }
 }
 else {
 expert_add_info ( pinfo , channel_type , & ei_mac_no_logical_channel ) ;
 }
 channel_type = proto_tree_add_uint ( hsdsch_tree , hf_mac_channel , tvb , 0 , 0 , MAC_DCCH ) ;
 PROTO_ITEM_SET_GENERATED ( channel_type ) ;
 channel_type = proto_tree_add_uint ( hsdsch_tree , hf_mac_macdflowd_id , tvb , 0 , 0 , macinf -> macdflow_id [ pos ] ) ;
 PROTO_ITEM_SET_GENERATED ( channel_type ) ;
 call_dissector_with_data ( rlc_dcch_handle , next_tvb , pinfo , tree , data ) ;
 break ;
 case MAC_CONTENT_PS_DTCH : proto_item_append_text ( ti , " (PS DTCH)" ) ;
 channel_type = proto_tree_add_uint ( hsdsch_tree , hf_mac_lch_id , tvb , 0 , 0 , macinf -> lchid [ pos ] ) ;
 PROTO_ITEM_SET_GENERATED ( channel_type ) ;
 if ( macinf -> lchid [ pos ] != 255 ) {
 if ( macinf -> fake_chid [ pos ] ) {
 expert_add_info ( pinfo , channel_type , & ei_mac_faked_logical_channel_id ) ;
 }
 }
 else {
 expert_add_info ( pinfo , channel_type , & ei_mac_no_logical_channel ) ;
 }
 channel_type = proto_tree_add_uint ( hsdsch_tree , hf_mac_channel , tvb , 0 , 0 , MAC_DTCH ) ;
 PROTO_ITEM_SET_GENERATED ( channel_type ) ;
 channel_type = proto_tree_add_uint ( hsdsch_tree , hf_mac_macdflowd_id , tvb , 0 , 0 , macinf -> macdflow_id [ pos ] ) ;
 PROTO_ITEM_SET_GENERATED ( channel_type ) ;
 call_dissector_with_data ( rlc_ps_dtch_handle , next_tvb , pinfo , tree , data ) ;
 break ;
 case MAC_CONTENT_CS_DTCH : proto_item_append_text ( ti , " (CS DTCH)" ) ;
 break ;
 default : proto_item_append_text ( ti , " (Unknown HSDSCH Content)" ) ;
 expert_add_info_format ( pinfo , NULL , & ei_mac_unknown_content , "Unknown HSDSCH Content" ) ;
 }
 return tvb_captured_length ( tvb ) ;
 }