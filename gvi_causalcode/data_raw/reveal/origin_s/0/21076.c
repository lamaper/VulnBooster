void dissect_coap_payload ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * coap_tree , proto_tree * parent_tree , gint offset , gint offset_end , guint8 code_class , coap_info * coinfo , coap_common_dissect_t * dissect_hf , gboolean oscore ) {
 proto_tree * payload_tree ;
 proto_item * payload_item , * length_item ;
 tvbuff_t * payload_tvb ;
 guint payload_length = offset_end - offset ;
 const char * coap_ctype_str_dis ;
 char str_payload [ 80 ] ;
 if ( coinfo -> ctype_value == DEFAULT_COAP_CTYPE_VALUE ) {
 if ( ( code_class >= 4 ) && ( code_class <= 5 ) ) {
 coinfo -> ctype_str = "text/plain;
 charset=utf-8" ;
 coap_ctype_str_dis = "text/plain" ;
 }
 else {
 coinfo -> ctype_str = "application/octet-stream" ;
 coap_ctype_str_dis = coinfo -> ctype_str ;
 }
 }
 else if ( coinfo -> ctype_value == 0 ) {
 coap_ctype_str_dis = "text/plain" ;
 }
 else {
 coap_ctype_str_dis = coinfo -> ctype_str ;
 }
 g_snprintf ( str_payload , sizeof ( str_payload ) , "Payload Content-Format: %s%s, Length: %u" , coinfo -> ctype_str , coinfo -> ctype_value == DEFAULT_COAP_CTYPE_VALUE ? " (no Content-Format)" : "" , payload_length ) ;
 payload_item = proto_tree_add_string ( coap_tree , dissect_hf -> hf . payload , tvb , offset , payload_length , str_payload ) ;
 payload_tree = proto_item_add_subtree ( payload_item , dissect_hf -> ett . payload ) ;
 proto_tree_add_string ( payload_tree , dissect_hf -> hf . payload_desc , tvb , offset , 0 , coinfo -> ctype_str ) ;
 length_item = proto_tree_add_uint ( payload_tree , dissect_hf -> hf . payload_length , tvb , offset , 0 , payload_length ) ;
 PROTO_ITEM_SET_GENERATED ( length_item ) ;
 payload_tvb = tvb_new_subset_length ( tvb , offset , payload_length ) ;
 dissector_try_string ( media_type_dissector_table , coap_ctype_str_dis , payload_tvb , pinfo , parent_tree , NULL ) ;
 if ( coinfo -> object_security && ! oscore ) {
 proto_item_set_text ( payload_item , "Encrypted OSCORE Data" ) ;
 call_dissector_with_data ( oscore_handle , payload_tvb , pinfo , parent_tree , coinfo -> oscore_info ) ;
 }
 }