static int dissect_pbb_message ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , guint offset ) {
 proto_tree * message_tree = NULL ;
 proto_tree * header_tree = NULL ;
 proto_tree * headerFlags_tree = NULL ;
 proto_item * message_item = NULL ;
 proto_item * header_item = NULL ;
 proto_item * headerFlags_item = NULL ;
 guint8 messageType ;
 guint8 messageFlags ;
 guint16 messageLength , headerLength , messageEnd ;
 guint8 addressSize , addressType ;
 if ( tvb_reported_length ( tvb ) - offset < 6 ) {
 proto_tree_add_expert_format ( tree , pinfo , & ei_packetbb_error , tvb , offset , - 1 , "Not enough octets for minimal message header" ) ;
 return tvb_reported_length ( tvb ) ;
 }
 messageType = tvb_get_guint8 ( tvb , offset ) ;
 messageFlags = tvb_get_guint8 ( tvb , offset + 1 ) ;
 messageLength = tvb_get_ntohs ( tvb , offset + 2 ) ;
 addressSize = ( messageFlags & 0x0f ) + 1 ;
 switch ( addressSize ) {
 case 4 : addressType = 0 ;
 break ;
 case 16 : addressType = 1 ;
 break ;
 case 6 : addressType = 2 ;
 break ;
 default : addressType = 3 ;
 break ;
 }
 messageEnd = offset + messageLength ;
 headerLength = 4 ;
 if ( ( messageFlags & MSG_HEADER_HASORIG ) != 0 ) {
 headerLength += addressSize ;
 }
 if ( ( messageFlags & MSG_HEADER_HASHOPLIMIT ) != 0 ) {
 headerLength ++ ;
 }
 if ( ( messageFlags & MSG_HEADER_HASHOPCOUNT ) != 0 ) {
 headerLength ++ ;
 }
 if ( ( messageFlags & MSG_HEADER_HASSEQNR ) != 0 ) {
 headerLength += 2 ;
 }
 if ( tvb_reported_length ( tvb ) - offset < messageLength ) {
 proto_tree_add_expert_format ( tree , pinfo , & ei_packetbb_error , tvb , offset , - 1 , "Not enough octets for message" ) ;
 return tvb_reported_length ( tvb ) ;
 }
 message_item = proto_tree_add_item ( tree , hf_packetbb_msg , tvb , offset , messageLength , ENC_NA ) ;
 message_tree = proto_item_add_subtree ( message_item , ett_packetbb_msg [ messageType ] ) ;
 proto_item_append_text ( message_item , " (%s)" , val_to_str_const ( messageType , msgheader_type_vals , "Unknown type" ) ) ;
 header_item = proto_tree_add_item ( message_tree , hf_packetbb_msgheader , tvb , offset , headerLength , ENC_NA ) ;
 header_tree = proto_item_add_subtree ( header_item , ett_packetbb_msgheader ) ;
 proto_tree_add_item ( header_tree , hf_packetbb_msgheader_type , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 headerFlags_item = proto_tree_add_uint ( header_tree , hf_packetbb_msgheader_flags , tvb , offset + 1 , 1 , messageFlags & 0xf8 ) ;
 headerFlags_tree = proto_item_add_subtree ( headerFlags_item , ett_packetbb_msgheader_flags ) ;
 proto_tree_add_boolean ( headerFlags_tree , hf_packetbb_msgheader_flags_mhasorig , tvb , offset + 1 , 1 , messageFlags ) ;
 proto_tree_add_boolean ( headerFlags_tree , hf_packetbb_msgheader_flags_mhashoplimit , tvb , offset + 1 , 1 , messageFlags ) ;
 proto_tree_add_boolean ( headerFlags_tree , hf_packetbb_msgheader_flags_mhashopcount , tvb , offset + 1 , 1 , messageFlags ) ;
 proto_tree_add_boolean ( headerFlags_tree , hf_packetbb_msgheader_flags_mhasseqnr , tvb , offset + 1 , 1 , messageFlags ) ;
 proto_tree_add_uint ( header_tree , hf_packetbb_msgheader_addresssize , tvb , offset + 1 , 1 , ( messageFlags & 0x0f ) + 1 ) ;
 proto_tree_add_item ( header_tree , hf_packetbb_msgheader_size , tvb , offset + 2 , 2 , ENC_BIG_ENDIAN ) ;
 offset += 4 ;
 if ( ( messageFlags & MSG_HEADER_HASORIG ) != 0 ) {
 switch ( addressSize ) {
 case 4 : proto_tree_add_item ( header_tree , hf_packetbb_msgheader_origaddripv4 , tvb , offset , addressSize , ENC_BIG_ENDIAN ) ;
 break ;
 case 16 : proto_tree_add_item ( header_tree , hf_packetbb_msgheader_origaddripv6 , tvb , offset , addressSize , ENC_NA ) ;
 break ;
 case 6 : proto_tree_add_item ( header_tree , hf_packetbb_msgheader_origaddrmac , tvb , offset , addressSize , ENC_NA ) ;
 break ;
 default : proto_tree_add_item ( header_tree , hf_packetbb_msgheader_origaddrcustom , tvb , offset , addressSize , ENC_NA ) ;
 break ;
 }
 offset += addressSize ;
 }
 if ( ( messageFlags & MSG_HEADER_HASHOPLIMIT ) != 0 ) {
 proto_tree_add_item ( header_tree , hf_packetbb_msgheader_hoplimit , tvb , offset ++ , 1 , ENC_BIG_ENDIAN ) ;
 }
 if ( ( messageFlags & MSG_HEADER_HASHOPCOUNT ) != 0 ) {
 proto_tree_add_item ( header_tree , hf_packetbb_msgheader_hopcount , tvb , offset ++ , 1 , ENC_BIG_ENDIAN ) ;
 }
 if ( ( messageFlags & MSG_HEADER_HASSEQNR ) != 0 ) {
 proto_tree_add_item ( header_tree , hf_packetbb_msgheader_seqnr , tvb , offset , 2 , ENC_BIG_ENDIAN ) ;
 offset += 2 ;
 }
 if ( offset >= messageEnd ) {
 return tvb_reported_length ( tvb ) ;
 }
 offset = dissect_pbb_tlvblock ( tvb , pinfo , message_tree , offset , messageEnd , 0 , TLV_CAT_MESSAGE ) ;
 while ( offset < messageEnd ) {
 offset = dissect_pbb_addressblock ( tvb , pinfo , message_tree , offset , messageEnd , addressType , addressSize ) ;
 }
 return offset ;
 }