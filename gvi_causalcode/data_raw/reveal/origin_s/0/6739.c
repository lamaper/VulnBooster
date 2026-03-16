static int dissect_mac_fdd_dch ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , void * data ) {
 guint16 pos ;
 guint8 bitoffs = 0 ;
 umts_mac_info * macinf ;
 fp_info * fpinf ;
 rlc_info * rlcinf ;
 proto_tree * dch_tree = NULL ;
 proto_item * channel_type ;
 tvbuff_t * next_tvb ;
 proto_item * ti = NULL ;
 col_set_str ( pinfo -> cinfo , COL_PROTOCOL , "MAC" ) ;
 ti = proto_tree_add_item ( tree , proto_umts_mac , tvb , 0 , - 1 , ENC_NA ) ;
 dch_tree = proto_item_add_subtree ( ti , ett_mac_dch ) ;
 macinf = ( umts_mac_info * ) p_get_proto_data ( wmem_file_scope ( ) , pinfo , proto_umts_mac , 0 ) ;
 fpinf = ( fp_info * ) p_get_proto_data ( wmem_file_scope ( ) , pinfo , proto_fp , 0 ) ;
 rlcinf = ( rlc_info * ) p_get_proto_data ( wmem_file_scope ( ) , pinfo , proto_rlc , 0 ) ;
 if ( ! macinf || ! fpinf ) {
 proto_tree_add_expert ( dch_tree , pinfo , & ei_mac_per_frame_info_missing , tvb , 0 , - 1 ) ;
 return 1 ;
 }
 pos = fpinf -> cur_tb ;
 if ( macinf -> ctmux [ pos ] ) {
 if ( rlcinf ) {
 rlcinf -> rbid [ fpinf -> cur_tb ] = tvb_get_bits8 ( tvb , bitoffs , 4 ) + 1 ;
 }
 proto_tree_add_bits_item ( dch_tree , hf_mac_ct , tvb , 0 , 4 , ENC_BIG_ENDIAN ) ;
 bitoffs = 4 ;
 }
 if ( bitoffs ) {
 next_tvb = tvb_new_octet_aligned ( tvb , bitoffs , fpinf -> chan_tf_size [ pos ] - bitoffs ) ;
 add_new_data_source ( pinfo , next_tvb , "Octet-Aligned DCCH Data" ) ;
 }
 else next_tvb = tvb ;
 switch ( macinf -> content [ pos ] ) {
 case MAC_CONTENT_DCCH : proto_item_append_text ( ti , " (DCCH)" ) ;
 channel_type = proto_tree_add_uint ( dch_tree , hf_mac_lch_id , tvb , 0 , 0 , macinf -> lchid [ pos ] ) ;
 PROTO_ITEM_SET_GENERATED ( channel_type ) ;
 if ( macinf -> lchid [ pos ] != 255 ) {
 if ( macinf -> fake_chid [ pos ] ) {
 expert_add_info ( pinfo , channel_type , & ei_mac_faked_logical_channel_id ) ;
 }
 }
 else {
 expert_add_info ( pinfo , channel_type , & ei_mac_no_logical_channel ) ;
 }
 channel_type = proto_tree_add_uint ( dch_tree , hf_mac_channel , tvb , 0 , 0 , MAC_DCCH ) ;
 PROTO_ITEM_SET_GENERATED ( channel_type ) ;
 channel_type = proto_tree_add_uint ( dch_tree , hf_mac_trch_id , tvb , 0 , 0 , macinf -> trchid [ pos ] ) ;
 PROTO_ITEM_SET_GENERATED ( channel_type ) ;
 call_dissector_with_data ( rlc_dcch_handle , next_tvb , pinfo , tree , data ) ;
 break ;
 case MAC_CONTENT_PS_DTCH : proto_item_append_text ( ti , " (PS DTCH)" ) ;
 channel_type = proto_tree_add_uint ( dch_tree , hf_mac_lch_id , tvb , 0 , 0 , macinf -> lchid [ pos ] ) ;
 PROTO_ITEM_SET_GENERATED ( channel_type ) ;
 if ( macinf -> lchid [ pos ] == 255 ) {
 expert_add_info ( pinfo , channel_type , & ei_mac_no_logical_channel ) ;
 }
 channel_type = proto_tree_add_uint ( dch_tree , hf_mac_channel , tvb , 0 , 0 , MAC_DTCH ) ;
 PROTO_ITEM_SET_GENERATED ( channel_type ) ;
 call_dissector_with_data ( rlc_ps_dtch_handle , next_tvb , pinfo , tree , data ) ;
 break ;
 case MAC_CONTENT_CS_DTCH : proto_item_append_text ( ti , " (CS DTCH)" ) ;
 channel_type = proto_tree_add_uint ( dch_tree , hf_mac_lch_id , tvb , 0 , 0 , macinf -> lchid [ pos ] ) ;
 PROTO_ITEM_SET_GENERATED ( channel_type ) ;
 if ( macinf -> lchid [ pos ] != 255 ) {
 if ( macinf -> fake_chid [ pos ] ) {
 expert_add_info ( pinfo , channel_type , & ei_mac_faked_logical_channel_id ) ;
 }
 }
 else {
 expert_add_info ( pinfo , channel_type , & ei_mac_no_logical_channel ) ;
 }
 channel_type = proto_tree_add_uint ( dch_tree , hf_mac_channel , tvb , 0 , 0 , MAC_DTCH ) ;
 PROTO_ITEM_SET_GENERATED ( channel_type ) ;
 channel_type = proto_tree_add_uint ( dch_tree , hf_mac_trch_id , tvb , 0 , 0 , macinf -> trchid [ pos ] ) ;
 PROTO_ITEM_SET_GENERATED ( channel_type ) ;
 break ;
 default : proto_item_append_text ( ti , " (Unknown DCH Content)" ) ;
 expert_add_info_format ( pinfo , NULL , & ei_mac_unknown_content , "Unknown DCH Content" ) ;
 }
 return tvb_captured_length ( tvb ) ;
 }