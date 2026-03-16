static void dtap_gcc_set_param ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo _U_ , guint32 offset , guint len ) {
 guint32 curr_offset ;
 guint32 consumed ;
 guint curr_len ;
 curr_offset = offset ;
 curr_len = len ;
 proto_tree_add_bits_item ( tree , hf_gsm_a_spare_bits , tvb , curr_offset << 3 , 4 , ENC_NA ) ;
 ELEM_MAND_V ( GSM_A_PDU_TYPE_DTAP , DE_GCC_STATE_ATTR , NULL ) ;
 }