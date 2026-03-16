static int dissect_amf ( tvbuff_t * tvb , packet_info * pinfo _U_ , proto_tree * tree , void * data _U_ ) {
 proto_item * ti ;
 proto_tree * amf_tree , * headers_tree , * messages_tree ;
 int offset ;
 guint header_count , message_count , i ;
 guint string_length ;
 guint header_length , message_length ;
 gboolean amf3_encoding = FALSE ;
 ti = proto_tree_add_item ( tree , proto_amf , tvb , 0 , - 1 , ENC_NA ) ;
 amf_tree = proto_item_add_subtree ( ti , ett_amf ) ;
 offset = 0 ;
 proto_tree_add_item ( amf_tree , hf_amf_version , tvb , offset , 2 , ENC_BIG_ENDIAN ) ;
 offset += 2 ;
 header_count = tvb_get_ntohs ( tvb , offset ) ;
 proto_tree_add_uint ( amf_tree , hf_amf_header_count , tvb , offset , 2 , header_count ) ;
 offset += 2 ;
 if ( header_count != 0 ) {
 headers_tree = proto_tree_add_subtree ( amf_tree , tvb , offset , - 1 , ett_amf_headers , NULL , "Headers" ) ;
 for ( i = 0 ;
 i < header_count ;
 i ++ ) {
 string_length = tvb_get_ntohs ( tvb , offset ) ;
 proto_tree_add_item ( headers_tree , hf_amf_header_name , tvb , offset , 2 , ENC_UTF_8 | ENC_BIG_ENDIAN ) ;
 offset += 2 + string_length ;
 proto_tree_add_item ( headers_tree , hf_amf_header_must_understand , tvb , offset , 1 , ENC_NA ) ;
 offset += 1 ;
 header_length = tvb_get_ntohl ( tvb , offset ) ;
 if ( header_length == 0xFFFFFFFF ) proto_tree_add_uint_format_value ( headers_tree , hf_amf_header_length , tvb , offset , 4 , header_length , "Unknown" ) ;
 else proto_tree_add_uint ( headers_tree , hf_amf_header_length , tvb , offset , 4 , header_length ) ;
 offset += 4 ;
 if ( amf3_encoding ) offset = dissect_amf3_value_type ( tvb , offset , headers_tree , NULL ) ;
 else offset = dissect_amf0_value_type ( tvb , offset , headers_tree , & amf3_encoding , NULL ) ;
 }
 }
 message_count = tvb_get_ntohs ( tvb , offset ) ;
 proto_tree_add_uint ( amf_tree , hf_amf_message_count , tvb , offset , 2 , message_count ) ;
 offset += 2 ;
 if ( message_count != 0 ) {
 messages_tree = proto_tree_add_subtree ( amf_tree , tvb , offset , - 1 , ett_amf_messages , NULL , "Messages" ) ;
 for ( i = 0 ;
 i < message_count ;
 i ++ ) {
 string_length = tvb_get_ntohs ( tvb , offset ) ;
 proto_tree_add_item ( messages_tree , hf_amf_message_target_uri , tvb , offset , 2 , ENC_UTF_8 | ENC_BIG_ENDIAN ) ;
 offset += 2 + string_length ;
 string_length = tvb_get_ntohs ( tvb , offset ) ;
 proto_tree_add_item ( messages_tree , hf_amf_message_response_uri , tvb , offset , 2 , ENC_UTF_8 | ENC_BIG_ENDIAN ) ;
 offset += 2 + string_length ;
 message_length = tvb_get_ntohl ( tvb , offset ) ;
 if ( message_length == 0xFFFFFFFF ) proto_tree_add_uint_format_value ( messages_tree , hf_amf_message_length , tvb , offset , 4 , message_length , "Unknown" ) ;
 else proto_tree_add_uint ( messages_tree , hf_amf_message_length , tvb , offset , 4 , message_length ) ;
 offset += 4 ;
 offset = dissect_rtmpt_body_command ( tvb , offset , messages_tree , FALSE ) ;
 }
 }
 return tvb_captured_length ( tvb ) ;
 }