void proto_register_coap ( void ) {
 static hf_register_info hf [ ] = {
 {
 & hf_coap_version , {
 "Version" , "coap.version" , FT_UINT8 , BASE_DEC , NULL , COAP_VERSION_MASK , NULL , HFILL }
 }
 , {
 & hf_coap_ttype , {
 "Type" , "coap.type" , FT_UINT8 , BASE_DEC , VALS ( vals_ttype ) , COAP_TYPE_MASK , NULL , HFILL }
 }
 , {
 & hf_coap_token_len , {
 "Token Length" , "coap.token_len" , FT_UINT8 , BASE_DEC , NULL , COAP_TOKEN_LEN_MASK , NULL , HFILL }
 }
 , {
 & hf_coap_token , {
 "Token" , "coap.token" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_coap_mid , {
 "Message ID" , "coap.mid" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_coap_response_in , {
 "Response In" , "coap.response_in" , FT_FRAMENUM , BASE_NONE , NULL , 0x0 , "The response to this CoAP request is in this frame" , HFILL }
 }
 , {
 & hf_coap_response_to , {
 "Request In" , "coap.response_to" , FT_FRAMENUM , BASE_NONE , NULL , 0x0 , "This is a response to the CoAP request in this frame" , HFILL }
 }
 , {
 & hf_coap_response_time , {
 "Response Time" , "coap.response_time" , FT_RELATIVE_TIME , BASE_NONE , NULL , 0x0 , "The time between the Call and the Reply" , HFILL }
 }
 , {
 & hf_coap_oscore_kid , {
 "OSCORE Key ID" , "coap.oscore_kid" , FT_BYTES , BASE_NONE , NULL , 0x0 , "Matched OSCORE Key ID" , HFILL }
 }
 , {
 & hf_coap_oscore_kid_context , {
 "OSCORE Key ID Context" , "coap.oscore_kid_context" , FT_BYTES , BASE_NONE , NULL , 0x0 , "Matched OSCORE Key ID Context" , HFILL }
 }
 , {
 & hf_coap_oscore_piv , {
 "OSCORE Partial IV" , "coap.oscore_piv" , FT_BYTES , BASE_NONE , NULL , 0x0 , "Matched OSCORE Partial IV" , HFILL }
 }
 , COAP_COMMON_HF_LIST ( dissect_coap_hf , "coap" ) }
 ;
 static gint * ett [ ] = {
 & ett_coap , COAP_COMMON_ETT_LIST ( dissect_coap_hf ) }
 ;
 static ei_register_info ei [ ] = {
 COAP_COMMON_EI_LIST ( dissect_coap_hf , "coap" ) }
 ;
 expert_module_t * expert_coap ;
 proto_coap = proto_register_protocol ( "Constrained Application Protocol" , "CoAP" , "coap" ) ;
 proto_register_field_array ( proto_coap , hf , array_length ( hf ) ) ;
 proto_register_subtree_array ( ett , array_length ( ett ) ) ;
 expert_coap = expert_register_protocol ( proto_coap ) ;
 expert_register_field_array ( expert_coap , ei , array_length ( ei ) ) ;
 coap_handle = register_dissector ( "coap" , dissect_coap , proto_coap ) ;
 }