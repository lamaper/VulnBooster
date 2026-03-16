static int dissect_pcp_message_error ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , int offset ) {
 gint32 error_num ;
 pcp_conv_info_t * pcp_conv_info ;
 col_append_str ( pinfo -> cinfo , COL_INFO , "[ERROR] " ) ;
 proto_tree_add_item ( tree , hf_pcp_pdu_error , tvb , offset , 4 , ENC_BIG_ENDIAN ) ;
 error_num = tvb_get_ntohl ( tvb , offset ) ;
 col_append_fstr ( pinfo -> cinfo , COL_INFO , "error=%s " , val_to_str ( error_num , packettypenames_errors , "Unknown Error:%i" ) ) ;
 offset += 4 ;
 if ( error_num == PM_ERR_NAME ) {
 pcp_conv_info = get_pcp_conversation_info ( pinfo ) ;
 pcp_conv_info -> pmid_name_candidates = wmem_array_new ( wmem_file_scope ( ) , sizeof ( guint8 * ) ) ;
 }
 return offset ;
 }