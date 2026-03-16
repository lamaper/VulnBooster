static int dissect_pcp_message_user_auth ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , int offset ) {
 col_append_fstr ( pinfo -> cinfo , COL_INFO , "[%s]" , val_to_str ( PCP_PDU_USER_AUTH , packettypenames , "Unknown Type:0x%02x" ) ) ;
 proto_tree_add_item ( tree , hf_pcp_user_auth_payload , tvb , offset , - 1 , ENC_NA ) ;
 return tvb_reported_length ( tvb ) ;
 }