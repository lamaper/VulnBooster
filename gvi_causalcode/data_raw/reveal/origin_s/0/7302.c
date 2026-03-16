static guint16 de_tp_ue_test_loop_mode ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo _U_ , guint32 offset , guint len _U_ , gchar * add_string _U_ , int string_len _U_ ) {
 guint32 curr_offset ;
 guchar oct ;
 guint8 lb_setup_length , i , j ;
 guint16 value ;
 proto_tree * subtree ;
 curr_offset = offset ;
 oct = tvb_get_guint8 ( tvb , curr_offset ) ;
 proto_tree_add_item ( tree , hf_gsm_a_dtap_ue_test_loop_mode , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 curr_offset += 1 ;
 switch ( oct & 0x03 ) {
 case 0 : {
 lb_setup_length = tvb_get_guint8 ( tvb , curr_offset ) ;
 curr_offset += 1 ;
 for ( i = 0 , j = 0 ;
 ( i < lb_setup_length ) && ( j < 4 ) ;
 i += 3 , j ++ ) {
 subtree = proto_tree_add_subtree_format ( tree , tvb , curr_offset , 3 , ett_ue_test_loop_mode , NULL , "LB setup RB IE: %d" , j + 1 ) ;
 value = tvb_get_ntohs ( tvb , curr_offset ) ;
 proto_tree_add_uint_format_value ( subtree , hf_gsm_a_dtap_uplink_rlc_sdu_size , tvb , curr_offset , 2 , value , "%d bits" , value ) ;
 curr_offset += 2 ;
 proto_tree_add_item ( subtree , hf_gsm_a_dtap_radio_bearer , tvb , curr_offset , 1 , ENC_NA ) ;
 curr_offset += 1 ;
 }
 break ;
 }
 case 2 : oct = tvb_get_guint8 ( tvb , curr_offset ) ;
 curr_offset += 1 ;
 proto_tree_add_uint ( tree , hf_gsm_a_dtap_mbms_short_transmission_identity , tvb , curr_offset , 1 , ( oct & 0x1f ) + 1 ) ;
 break ;
 }
 return ( curr_offset - offset ) ;
 }