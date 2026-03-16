static int dissect_AllJoyn_name_server ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , void * data _U_ ) {
 proto_item * alljoyn_item , * header_item ;
 proto_tree * alljoyn_tree , * header_tree ;
 guint8 questions , answers ;
 guint8 version ;
 int offset = 0 ;
 col_set_str ( pinfo -> cinfo , COL_PROTOCOL , "ALLJOYN-NS" ) ;
 col_clear ( pinfo -> cinfo , COL_INFO ) ;
 alljoyn_item = proto_tree_add_item ( tree , proto_AllJoyn_ns , tvb , 0 , - 1 , ENC_NA ) ;
 alljoyn_tree = proto_item_add_subtree ( alljoyn_item , ett_alljoyn_ns ) ;
 header_item = proto_tree_add_item ( alljoyn_tree , hf_alljoyn_ns_header , tvb , offset , 4 , ENC_NA ) ;
 header_tree = proto_item_add_subtree ( header_item , ett_alljoyn_ns_header ) ;
 proto_tree_add_item ( header_tree , hf_alljoyn_ns_sender_version , tvb , offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( header_tree , hf_alljoyn_ns_message_version , tvb , offset , 1 , ENC_NA ) ;
 version = tvb_get_guint8 ( tvb , offset ) & 0xF ;
 offset += 1 ;
 col_add_fstr ( pinfo -> cinfo , COL_INFO , "VERSION %u" , version ) ;
 if ( version > 1 ) col_append_str ( pinfo -> cinfo , COL_INFO , " (UNSUPPORTED)" ) ;
 proto_tree_add_item ( header_tree , hf_alljoyn_ns_questions , tvb , offset , 1 , ENC_NA ) ;
 questions = tvb_get_guint8 ( tvb , offset ) ;
 offset += 1 ;
 proto_tree_add_item ( header_tree , hf_alljoyn_ns_answers , tvb , offset , 1 , ENC_NA ) ;
 answers = tvb_get_guint8 ( tvb , offset ) ;
 offset += 1 ;
 if ( answers > 0 ) col_append_str ( pinfo -> cinfo , COL_INFO , " ISAT" ) ;
 if ( questions > 0 ) col_append_str ( pinfo -> cinfo , COL_INFO , " WHOHAS" ) ;
 proto_tree_add_item ( header_tree , hf_alljoyn_ns_timer , tvb , offset , 1 , ENC_NA ) ;
 offset += 1 ;
 if ( tree ) {
 ns_parse_questions ( tvb , & offset , alljoyn_tree , questions , version ) ;
 switch ( version ) {
 case 0 : ns_parse_answers_v0 ( tvb , & offset , alljoyn_tree , answers ) ;
 break ;
 case 1 : ns_parse_answers_v1 ( tvb , & offset , alljoyn_tree , answers ) ;
 break ;
 default : break ;
 }
 }
 return tvb_reported_length ( tvb ) ;
 }