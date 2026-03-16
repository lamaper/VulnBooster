static void ardp_parse_header ( tvbuff_t * tvb , packet_info * pinfo , alljoyn_ardp_tree_data * tree_data ) {
 guint8 flags , header_length ;
 gint eaklen , packet_length ;
 guint16 data_length ;
 packet_length = tvb_reported_length ( tvb ) ;
 flags = tvb_get_guint8 ( tvb , 0 ) ;
 tree_data -> syn = ( flags & ARDP_SYN ) != 0 ;
 tree_data -> ack = ( flags & ARDP_ACK ) != 0 ;
 tree_data -> eak = ( flags & ARDP_EAK ) != 0 ;
 tree_data -> rst = ( flags & ARDP_RST ) != 0 ;
 tree_data -> nul = ( flags & ARDP_NUL ) != 0 ;
 header_length = 2 * tvb_get_guint8 ( tvb , ARDP_HEADER_LEN_OFFSET ) ;
 if ( packet_length < ARDP_DATA_LENGTH_OFFSET + 2 ) {
 set_pinfo_desegment ( pinfo , 0 , ARDP_DATA_LENGTH_OFFSET + 2 - packet_length ) ;
 tree_data -> offset = ARDP_HEADER_LEN_OFFSET + 1 ;
 return ;
 }
 data_length = tvb_get_ntohs ( tvb , ARDP_DATA_LENGTH_OFFSET ) ;
 if ( packet_length < header_length + data_length ) {
 set_pinfo_desegment ( pinfo , 0 , header_length + data_length - packet_length ) ;
 tree_data -> offset = ARDP_DATA_LENGTH_OFFSET + 2 ;
 return ;
 }
 proto_tree_add_item ( tree_data -> alljoyn_tree , hf_ardp_syn_flag , tvb , tree_data -> offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree_data -> alljoyn_tree , hf_ardp_ack_flag , tvb , tree_data -> offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree_data -> alljoyn_tree , hf_ardp_eak_flag , tvb , tree_data -> offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree_data -> alljoyn_tree , hf_ardp_rst_flag , tvb , tree_data -> offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree_data -> alljoyn_tree , hf_ardp_nul_flag , tvb , tree_data -> offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree_data -> alljoyn_tree , hf_ardp_unused_flag , tvb , tree_data -> offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree_data -> alljoyn_tree , hf_ardp_version_field , tvb , tree_data -> offset , 1 , ENC_NA ) ;
 tree_data -> offset += 1 ;
 proto_tree_add_item ( tree_data -> alljoyn_tree , hf_ardp_hlen , tvb , tree_data -> offset , 1 , ENC_NA ) ;
 tree_data -> offset += 1 ;
 proto_tree_add_item ( tree_data -> alljoyn_tree , hf_ardp_src , tvb , tree_data -> offset , 2 , ENC_BIG_ENDIAN ) ;
 tree_data -> offset += 2 ;
 proto_tree_add_item ( tree_data -> alljoyn_tree , hf_ardp_dst , tvb , tree_data -> offset , 2 , ENC_BIG_ENDIAN ) ;
 tree_data -> offset += 2 ;
 proto_tree_add_item ( tree_data -> alljoyn_tree , hf_ardp_dlen , tvb , tree_data -> offset , 2 , ENC_BIG_ENDIAN ) ;
 tree_data -> offset += 2 ;
 proto_tree_add_item ( tree_data -> alljoyn_tree , hf_ardp_seq , tvb , tree_data -> offset , 4 , ENC_BIG_ENDIAN ) ;
 tree_data -> sequence = tvb_get_ntohl ( tvb , tree_data -> offset ) ;
 tree_data -> offset += 4 ;
 proto_tree_add_item ( tree_data -> alljoyn_tree , hf_ardp_ack , tvb , tree_data -> offset , 4 , ENC_BIG_ENDIAN ) ;
 tree_data -> acknowledge = tvb_get_ntohl ( tvb , tree_data -> offset ) ;
 tree_data -> offset += 4 ;
 if ( tree_data -> syn ) {
 proto_tree_add_item ( tree_data -> alljoyn_tree , hf_ardp_segmax , tvb , tree_data -> offset , 2 , ENC_BIG_ENDIAN ) ;
 tree_data -> offset += 2 ;
 proto_tree_add_item ( tree_data -> alljoyn_tree , hf_ardp_segbmax , tvb , tree_data -> offset , 2 , ENC_BIG_ENDIAN ) ;
 tree_data -> offset += 2 ;
 proto_tree_add_item ( tree_data -> alljoyn_tree , hf_ardp_dackt , tvb , tree_data -> offset , 4 , ENC_BIG_ENDIAN ) ;
 tree_data -> offset += 4 ;
 proto_tree_add_item ( tree_data -> alljoyn_tree , hf_ardp_options , tvb , tree_data -> offset , 2 , ENC_BIG_ENDIAN ) ;
 tree_data -> offset += 2 ;
 }
 else {
 proto_tree_add_item ( tree_data -> alljoyn_tree , hf_ardp_ttl , tvb , tree_data -> offset , 4 , ENC_BIG_ENDIAN ) ;
 tree_data -> offset += 4 ;
 proto_tree_add_item ( tree_data -> alljoyn_tree , hf_ardp_lcs , tvb , tree_data -> offset , 4 , ENC_BIG_ENDIAN ) ;
 tree_data -> offset += 4 ;
 proto_tree_add_item ( tree_data -> alljoyn_tree , hf_ardp_nsa , tvb , tree_data -> offset , 4 , ENC_BIG_ENDIAN ) ;
 tree_data -> offset += 4 ;
 proto_tree_add_item ( tree_data -> alljoyn_tree , hf_ardp_fss , tvb , tree_data -> offset , 4 , ENC_BIG_ENDIAN ) ;
 tree_data -> start_sequence = tvb_get_ntohl ( tvb , tree_data -> offset ) ;
 tree_data -> offset += 4 ;
 proto_tree_add_item ( tree_data -> alljoyn_tree , hf_ardp_fcnt , tvb , tree_data -> offset , 2 , ENC_BIG_ENDIAN ) ;
 tree_data -> fragment_count = tvb_get_ntohs ( tvb , tree_data -> offset ) ;
 tree_data -> offset += 2 ;
 eaklen = header_length - ARDP_FIXED_HDR_LEN ;
 if ( eaklen > 0 ) {
 if ( tree_data -> eak ) {
 proto_tree_add_item ( tree_data -> alljoyn_tree , hf_ardp_bmp , tvb , tree_data -> offset , eaklen , ENC_NA ) ;
 }
 tree_data -> offset += eaklen ;
 }
 }
 }