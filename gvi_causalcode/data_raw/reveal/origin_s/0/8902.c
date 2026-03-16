static void dissect_rsvp_3gpp_object ( proto_tree * ti _U_ , packet_info * pinfo , proto_tree * rsvp_object_tree , tvbuff_t * tvb , int offset , int obj_length , int rsvp_class _U_ , int c_type ) {
 guint16 length , ie_type ;
 offset += 3 ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_ctype , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 offset ++ ;
 obj_length = obj_length - 4 ;
 if ( c_type == 1 ) {
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_3gpp_obj_tid , tvb , offset , 4 , ENC_BIG_ENDIAN ) ;
 offset += 4 ;
 obj_length = obj_length - 4 ;
 while ( obj_length > 0 ) {
 length = tvb_get_ntohs ( tvb , offset ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_3gpp_obj_ie_len , tvb , offset , 2 , ENC_BIG_ENDIAN ) ;
 offset += 2 ;
 ie_type = tvb_get_ntohs ( tvb , offset ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_3gpp_obj_ie_type , tvb , offset , 2 , ENC_BIG_ENDIAN ) ;
 offset += 2 ;
 if ( ( ie_type == 0 ) || ( ie_type == 2 ) ) {
 guint8 tft_opcode , tft_n_pkt_flt ;
 int i ;
 if ( ie_type == 0 ) {
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_3gpp_obj_ue_ipv4_addr , tvb , offset , 4 , ENC_BIG_ENDIAN ) ;
 offset += 4 ;
 }
 else {
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_3gpp_obj_ue_ipv6_addr , tvb , offset , 16 , ENC_NA ) ;
 offset += 16 ;
 }
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_3gpp_obj_tft_d , tvb , offset , 4 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_3gpp_obj_tft_ns , tvb , offset , 4 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_3gpp_obj_tft_sr_id , tvb , offset , 4 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_3gpp_obj_tft_p , tvb , offset , 4 , ENC_BIG_ENDIAN ) ;
 tft_opcode = tvb_get_guint8 ( tvb , offset + 2 ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_3gpp_obj_tft_opcode , tvb , offset , 4 , ENC_BIG_ENDIAN ) ;
 tft_n_pkt_flt = tvb_get_guint8 ( tvb , offset + 3 ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_3gpp_obj_tft_n_pkt_flt , tvb , offset , 4 , ENC_BIG_ENDIAN ) ;
 offset += 4 ;
 if ( ( tft_opcode != 0x81 ) && ( tft_n_pkt_flt != 0 ) ) {
 for ( i = 0 ;
 i < tft_n_pkt_flt ;
 i ++ ) {
 proto_tree * flow_tree , * t2_tree ;
 guint16 pkt_flt_len , item_len , pf_cont_len ;
 guint8 pf_comp_type_id ;
 flow_tree = proto_tree_add_subtree_format ( rsvp_object_tree , tvb , offset , - 1 , ett_treelist [ TT_3GPP_OBJ_FLOW ] , & ti , "Flow Identifier Num %u" , i + 1 ) ;
 proto_tree_add_item ( flow_tree , hf_rsvp_3gpp_obj_flow_id , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 offset ++ ;
 item_len = 1 ;
 if ( ( tft_opcode == 0x05 ) || ( tft_opcode == 0x82 ) ) {
 proto_item_set_len ( ti , item_len ) ;
 continue ;
 }
 proto_tree_add_item ( flow_tree , hf_rsvp_3gpp_obj_pf_ev_prec , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 offset ++ ;
 pkt_flt_len = tvb_get_ntohs ( tvb , offset ) ;
 proto_tree_add_item ( flow_tree , hf_rsvp_3gpp_obj_pf_len , tvb , offset , 2 , ENC_BIG_ENDIAN ) ;
 item_len = item_len + pkt_flt_len + 1 ;
 offset += 2 ;
 proto_tree_add_item ( flow_tree , hf_rsvp_3gpp_obj_pf_type , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 offset ++ ;
 pf_cont_len = tvb_get_guint8 ( tvb , offset ) ;
 proto_tree_add_item ( flow_tree , hf_rsvp_3gpp_obj_pf_cont_len , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 offset ++ ;
 pf_comp_type_id = tvb_get_guint8 ( tvb , offset ) ;
 proto_tree_add_item ( flow_tree , hf_rsvp_3gpp_obj_pf_comp_type_id , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 offset ++ ;
 switch ( pf_comp_type_id ) {
 case 16 : proto_tree_add_item ( flow_tree , hf_rsvp_3gpp_obj_pf_src_ipv4 , tvb , offset , 4 , ENC_BIG_ENDIAN ) ;
 offset += 4 ;
 proto_tree_add_item ( flow_tree , hf_rsvp_3gpp_obj_pf_ipv4_mask , tvb , offset , 4 , ENC_BIG_ENDIAN ) ;
 offset += 4 ;
 pf_cont_len -= 11 ;
 break ;
 case 17 : proto_tree_add_item ( flow_tree , hf_rsvp_3gpp_obj_pf_dst_ipv4 , tvb , offset , 4 , ENC_BIG_ENDIAN ) ;
 offset += 4 ;
 proto_tree_add_item ( flow_tree , hf_rsvp_3gpp_obj_pf_ipv4_mask , tvb , offset , 4 , ENC_BIG_ENDIAN ) ;
 offset += 4 ;
 pf_cont_len -= 11 ;
 break ;
 case 32 : proto_tree_add_item ( flow_tree , hf_rsvp_3gpp_obj_pf_src_ipv6 , tvb , offset , 16 , ENC_NA ) ;
 offset += 16 ;
 proto_tree_add_item ( flow_tree , hf_rsvp_3gpp_obj_pf_ipv6_prefix_length , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 offset ++ ;
 pf_cont_len -= 20 ;
 break ;
 case 33 : proto_tree_add_item ( flow_tree , hf_rsvp_3gpp_obj_pf_dst_ipv6 , tvb , offset , 16 , ENC_NA ) ;
 offset += 16 ;
 proto_tree_add_item ( flow_tree , hf_rsvp_3gpp_obj_pf_ipv6_prefix_length , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 offset ++ ;
 pf_cont_len -= 20 ;
 break ;
 case 48 : proto_tree_add_item ( flow_tree , hf_rsvp_3gpp_obj_pf_prot_next , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 offset ++ ;
 pf_cont_len -= 4 ;
 break ;
 case 64 : proto_tree_add_item ( flow_tree , hf_rsvp_3gpp_obj_pf_dst_port , tvb , offset , 2 , ENC_BIG_ENDIAN ) ;
 offset += 2 ;
 pf_cont_len -= 5 ;
 break ;
 case 65 : proto_tree_add_uint_format_value ( rsvp_object_tree , hf_rsvp_3gpp_obj_pf_dst_port_range , tvb , offset , 4 , tvb_get_ntohs ( tvb , offset ) , "%u-%u" , tvb_get_ntohs ( tvb , offset ) , tvb_get_ntohs ( tvb , offset + 2 ) ) ;
 offset += 4 ;
 break ;
 case 80 : proto_tree_add_item ( flow_tree , hf_rsvp_3gpp_obj_pf_src_port , tvb , offset , 2 , ENC_BIG_ENDIAN ) ;
 offset += 2 ;
 pf_cont_len -= 5 ;
 break ;
 case 81 : proto_tree_add_uint_format_value ( rsvp_object_tree , hf_rsvp_3gpp_obj_pf_src_port_range , tvb , offset , 4 , tvb_get_ntohs ( tvb , offset ) , "Source Port range %u-%u" , tvb_get_ntohs ( tvb , offset ) , tvb_get_ntohs ( tvb , offset + 2 ) ) ;
 offset += 4 ;
 pf_cont_len -= 7 ;
 break ;
 case 96 : proto_tree_add_item ( flow_tree , hf_rsvp_3gpp_obj_pf_ipsec_spi , tvb , offset , 4 , ENC_BIG_ENDIAN ) ;
 offset += 4 ;
 pf_cont_len -= 7 ;
 break ;
 case 112 : proto_tree_add_item ( flow_tree , hf_rsvp_3gpp_obj_pf_tos_tc , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 offset ++ ;
 pf_cont_len -= 4 ;
 break ;
 case 128 : proto_tree_add_item ( flow_tree , hf_rsvp_3gpp_obj_pf_flow_lbl , tvb , offset , 3 , ENC_BIG_ENDIAN ) ;
 offset += 3 ;
 pf_cont_len -= 6 ;
 break ;
 case 129 : t2_tree = proto_tree_add_subtree ( flow_tree , tvb , offset , 17 , ett_treelist [ TT_3GPP_OBJ_T2 ] , NULL , "Type 2 Routing Header packet filter" ) ;
 proto_tree_add_item ( t2_tree , hf_rsvp_3gpp_obj_pf_ipv6 , tvb , offset , 16 , ENC_NA ) ;
 offset += 16 ;
 proto_tree_add_item ( t2_tree , hf_rsvp_3gpp_obj_pf_ipv6_prefix_length , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 offset ++ ;
 pf_cont_len -= 20 ;
 break ;
 case 130 : t2_tree = proto_tree_add_subtree ( flow_tree , tvb , offset , 17 , ett_treelist [ TT_3GPP_OBJ_HO ] , NULL , "Home address Option packet filter" ) ;
 proto_tree_add_item ( t2_tree , hf_rsvp_3gpp_obj_pf_ipv6 , tvb , offset , 16 , ENC_NA ) ;
 offset += 16 ;
 proto_tree_add_item ( t2_tree , hf_rsvp_3gpp_obj_pf_ipv6_prefix_length , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 offset ++ ;
 pf_cont_len -= 20 ;
 break ;
 default : proto_tree_add_expert ( flow_tree , pinfo , & ei_rsvp_packet_filter_component , tvb , offset , pf_cont_len - 2 ) ;
 offset = offset + pkt_flt_len - 5 ;
 pf_cont_len = 0 ;
 break ;
 }
 if ( pf_cont_len != 0 ) {
 proto_tree_add_item ( flow_tree , hf_rsvp_3gpp_obj_pf_treatment , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 offset ++ ;
 proto_tree_add_item ( flow_tree , hf_rsvp_3gpp_obj_pf_hint , tvb , offset , 4 , ENC_BIG_ENDIAN ) ;
 offset += 4 ;
 }
 proto_item_set_len ( ti , item_len ) ;
 }
 }
 if ( ( tft_opcode == 0x01 ) || ( tft_opcode == 0x06 ) || ( tft_opcode == 0x80 ) || ( tft_opcode == 0x81 ) || ( tft_opcode == 0x83 ) ) {
 gint32 tft_qos_list_len ;
 guint8 blob_len , item_len , padding_len ;
 gboolean verbose ;
 proto_tree * qos_tree , * qos_sub_blob_tree , * qos_att_tree ;
 int num = 0 , j , num_qos_att_set ;
 tft_qos_list_len = tvb_get_ntohs ( tvb , offset ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_3gpp_obj_tft_qos_list_len , tvb , offset , 2 , ENC_BIG_ENDIAN ) ;
 offset += 2 ;
 tft_qos_list_len -= 2 ;
 if ( tft_qos_list_len > 0 ) {
 while ( tft_qos_list_len > 0 ) {
 int bit_offset ;
 guint8 qos_attribute_set_len ;
 num ++ ;
 qos_tree = proto_tree_add_subtree_format ( rsvp_object_tree , tvb , offset , - 1 , ett_treelist [ TT_3GPP_OBJ_QOS ] , NULL , "QOS Flow Identifier Num %u" , num ) ;
 proto_tree_add_item ( qos_tree , hf_rsvp_3gpp_obj_flow_id , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 offset ++ ;
 tft_qos_list_len -- ;
 blob_len = tvb_get_guint8 ( tvb , offset ) ;
 proto_tree_add_item ( qos_tree , hf_rsvp_3gpp_r_qos_blob_len , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 offset ++ ;
 tft_qos_list_len -- ;
 ti = proto_tree_add_item ( qos_tree , hf_rsvp_3gpp_r_qos_blob , tvb , offset , blob_len , ENC_NA ) ;
 qos_sub_blob_tree = proto_item_add_subtree ( ti , ett_treelist [ TT_3GPP_OBJ_QOS_SUB_BLOB ] ) ;
 proto_tree_add_item ( qos_sub_blob_tree , hf_rsvp_3gpp_r_qos_blob_flow_pri , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( qos_sub_blob_tree , hf_rsvp_3gpp_r_qos_blob_num_qos_att_set , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 num_qos_att_set = ( tvb_get_guint8 ( tvb , offset ) & 0x0e ) >> 1 ;
 bit_offset = ( offset << 3 ) + 7 ;
 for ( j = 0 ;
 j < num_qos_att_set ;
 j ++ ) {
 qos_attribute_set_len = tvb_get_bits8 ( tvb , bit_offset , 4 ) ;
 qos_att_tree = proto_tree_add_subtree_format ( qos_sub_blob_tree , tvb , bit_offset >> 3 , qos_attribute_set_len , ett_treelist [ TT_3GPP_OBJ_QOS_SUB_BLOB ] , NULL , "QoS_ATTRIBUTE_SET %u(%u bytes)" , j + 1 , qos_attribute_set_len ) ;
 proto_tree_add_bits_item ( qos_att_tree , hf_rsvp_3gpp_qos_att_set_len , tvb , bit_offset , 4 , ENC_BIG_ENDIAN ) ;
 bit_offset += 4 ;
 if ( qos_attribute_set_len == 0 ) {
 break ;
 }
 proto_tree_add_bits_item ( qos_att_tree , hf_rsvp_3gpp_qos_attribute_set_id , tvb , bit_offset , 7 , ENC_BIG_ENDIAN ) ;
 bit_offset += 7 ;
 verbose = tvb_get_bits8 ( tvb , bit_offset , 1 ) ;
 proto_tree_add_bits_item ( qos_att_tree , hf_rsvp_3gpp_qos_attribute_verbose , tvb , bit_offset , 1 , ENC_BIG_ENDIAN ) ;
 bit_offset ++ ;
 if ( verbose == FALSE ) {
 proto_tree_add_bits_item ( qos_att_tree , hf_rsvp_3gpp_qos_attribute_prof_id , tvb , bit_offset , 16 , ENC_BIG_ENDIAN ) ;
 bit_offset += 16 ;
 }
 else {
 proto_tree_add_bits_item ( qos_att_tree , hf_rsvp_3gpp_qos_attribute_traff_cls , tvb , bit_offset , 3 , ENC_BIG_ENDIAN ) ;
 bit_offset += 3 ;
 proto_tree_add_bits_item ( qos_att_tree , hf_rsvp_3gpp_qos_attribute_peak_rate , tvb , bit_offset , 16 , ENC_BIG_ENDIAN ) ;
 bit_offset += 16 ;
 proto_tree_add_bits_item ( qos_att_tree , hf_rsvp_3gpp_qos_attribute_bucket_size , tvb , bit_offset , 16 , ENC_BIG_ENDIAN ) ;
 bit_offset += 16 ;
 proto_tree_add_bits_item ( qos_att_tree , hf_rsvp_3gpp_qos_attribute_token_rate , tvb , bit_offset , 16 , ENC_BIG_ENDIAN ) ;
 bit_offset += 16 ;
 proto_tree_add_bits_item ( qos_att_tree , hf_rsvp_3gpp_qos_attribute_max_latency , tvb , bit_offset , 16 , ENC_BIG_ENDIAN ) ;
 bit_offset += 8 ;
 proto_tree_add_bits_item ( qos_att_tree , hf_rsvp_3gpp_qos_attribute_max_loss_rte , tvb , bit_offset , 16 , ENC_BIG_ENDIAN ) ;
 bit_offset += 8 ;
 proto_tree_add_bits_item ( qos_att_tree , hf_rsvp_3gpp_qos_attribute_delay_var_sensitive , tvb , bit_offset , 16 , ENC_BIG_ENDIAN ) ;
 bit_offset += 1 ;
 }
 padding_len = 0 ;
 if ( ( bit_offset & 0x07 ) != 0 ) {
 padding_len = 8 - ( bit_offset & 0x07 ) ;
 proto_tree_add_bits_item ( qos_att_tree , hf_rsvp_3gpp_qos_attribute_reserved , tvb , bit_offset , padding_len , ENC_BIG_ENDIAN ) ;
 }
 bit_offset = bit_offset + padding_len ;
 }
 offset = offset + blob_len ;
 tft_qos_list_len = tft_qos_list_len - blob_len ;
 item_len = blob_len + 2 ;
 if ( tft_opcode == 0x81 ) {
 proto_tree_add_item ( qos_tree , hf_rsvp_3gpp_qos_result , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 offset ++ ;
 tft_qos_list_len -- ;
 item_len ++ ;
 }
 proto_item_set_len ( ti , item_len ) ;
 }
 }
 }
 else {
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_ie_data , tvb , offset , length - 2 , ENC_NA ) ;
 }
 obj_length = obj_length - length ;
 }
 }
 }
 }