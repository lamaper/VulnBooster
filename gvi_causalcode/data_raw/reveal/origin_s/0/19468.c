static int dissect_pcp_message_text ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , int offset ) {
 proto_item * pcp_text_item ;
 proto_tree * pcp_text_tree ;
 guint32 buflen ;
 col_append_fstr ( pinfo -> cinfo , COL_INFO , "[%s]" , val_to_str ( PCP_PDU_TEXT , packettypenames , "Unknown Type:0x%02x" ) ) ;
 pcp_text_item = proto_tree_add_item ( tree , hf_pcp_text , tvb , offset , - 1 , ENC_NA ) ;
 pcp_text_tree = proto_item_add_subtree ( pcp_text_item , ett_pcp ) ;
 proto_tree_add_item ( pcp_text_tree , hf_pcp_text_ident , tvb , offset , 4 , ENC_BIG_ENDIAN ) ;
 offset += 4 ;
 buflen = tvb_get_ntohl ( tvb , offset ) ;
 proto_tree_add_item ( pcp_text_tree , hf_pcp_text_buflen , tvb , offset , 4 , ENC_BIG_ENDIAN ) ;
 offset += 4 ;
 proto_tree_add_item ( pcp_text_tree , hf_pcp_text_buffer , tvb , offset , buflen , ENC_ASCII | ENC_NA ) ;
 offset += buflen ;
 return offset ;
 }