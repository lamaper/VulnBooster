static int dissect_pcp_message_creds ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , int offset ) {
 guint32 creds_length ;
 guint32 i ;
 col_append_fstr ( pinfo -> cinfo , COL_INFO , "[%s]" , val_to_str ( PCP_PDU_CREDS , packettypenames , "Unknown Type:0x%02x" ) ) ;
 proto_tree_add_item ( tree , hf_pcp_creds_number_of , tvb , offset , 4 , ENC_BIG_ENDIAN ) ;
 creds_length = tvb_get_ntohl ( tvb , offset ) ;
 offset += 4 ;
 for ( i = 0 ;
 i < creds_length ;
 i ++ ) {
 proto_tree_add_item ( tree , hf_pcp_creds_type , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 offset += 1 ;
 proto_tree_add_item ( tree , hf_pcp_creds_version , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 offset += 1 ;
 offset = dissect_pcp_partial_features ( tvb , pinfo , tree , offset ) ;
 }
 return offset ;
 }