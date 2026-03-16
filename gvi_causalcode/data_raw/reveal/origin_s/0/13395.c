static guint16 de_tp_epc_ue_tl_a_lb_setup ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo _U_ , guint32 offset , guint len _U_ , gchar * add_string _U_ , int string_len _U_ ) {
 guint32 curr_offset ;
 guint32 count , nb_lb ;
 guint8 drb ;
 proto_tree * lb_setup_tree = NULL ;
 proto_item * ti ;
 curr_offset = offset ;
 count = 0 ;
 nb_lb = len / 3 ;
 ti = proto_tree_add_uint ( tree , hf_gsm_a_dtap_num_lb_entities , tvb , curr_offset , 1 , nb_lb ) ;
 proto_item_set_len ( ti , len ) ;
 while ( ( count < nb_lb ) && ( count < 8 ) ) {
 lb_setup_tree = proto_tree_add_subtree_format ( tree , tvb , curr_offset , 3 , ett_epc_ue_tl_a_lb_setup , NULL , "LB entity %d" , count ) ;
 proto_tree_add_bits_item ( lb_setup_tree , hf_gsm_a_dtap_epc_ue_tl_a_ul_sdu_size , tvb , curr_offset << 3 , 16 , ENC_BIG_ENDIAN ) ;
 curr_offset += 2 ;
 drb = tvb_get_guint8 ( tvb , curr_offset ) & 0x1f ;
 proto_tree_add_uint_format_value ( lb_setup_tree , hf_gsm_a_dtap_epc_ue_tl_a_drb , tvb , curr_offset , 1 , drb , "%d (%d)" , drb + 1 , drb ) ;
 curr_offset ++ ;
 count ++ ;
 }
 EXTRANEOUS_DATA_CHECK ( len , curr_offset - offset , pinfo , & ei_gsm_a_dtap_extraneous_data ) ;
 return ( len ) ;
 }