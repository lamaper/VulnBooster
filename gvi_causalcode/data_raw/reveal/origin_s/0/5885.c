static int dissect_coap ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * parent_tree , void * data _U_ ) {
 gint offset = 0 ;
 proto_item * coap_root ;
 proto_item * pi ;
 proto_tree * coap_tree ;
 guint8 ttype ;
 guint8 token_len ;
 guint8 code ;
 guint8 code_class ;
 guint16 mid ;
 gint coap_length ;
 gchar * coap_token_str ;
 coap_info * coinfo ;
 conversation_t * conversation ;
 coap_conv_info * ccinfo ;
 coap_transaction * coap_trans = NULL ;
 coinfo = ( coap_info * ) p_get_proto_data ( wmem_file_scope ( ) , pinfo , proto_coap , 0 ) ;
 if ( coinfo == NULL ) {
 coinfo = wmem_new0 ( wmem_file_scope ( ) , coap_info ) ;
 p_add_proto_data ( wmem_file_scope ( ) , pinfo , proto_coap , 0 , coinfo ) ;
 }
 coap_length = tvb_reported_length ( tvb ) ;
 coinfo -> ctype_str = "" ;
 coinfo -> ctype_value = DEFAULT_COAP_CTYPE_VALUE ;
 col_set_str ( pinfo -> cinfo , COL_PROTOCOL , "CoAP" ) ;
 col_clear ( pinfo -> cinfo , COL_INFO ) ;
 coap_root = proto_tree_add_item ( parent_tree , proto_coap , tvb , offset , - 1 , ENC_NA ) ;
 coap_tree = proto_item_add_subtree ( coap_root , ett_coap ) ;
 proto_tree_add_item ( coap_tree , hf_coap_version , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( coap_tree , hf_coap_ttype , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 ttype = ( tvb_get_guint8 ( tvb , offset ) & COAP_TYPE_MASK ) >> 4 ;
 proto_tree_add_item ( coap_tree , hf_coap_token_len , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 token_len = tvb_get_guint8 ( tvb , offset ) & COAP_TOKEN_LEN_MASK ;
 offset += 1 ;
 code = dissect_coap_code ( tvb , coap_tree , & offset , & dissect_coap_hf , & code_class ) ;
 proto_tree_add_item ( coap_tree , hf_coap_mid , tvb , offset , 2 , ENC_BIG_ENDIAN ) ;
 mid = tvb_get_ntohs ( tvb , offset ) ;
 col_add_fstr ( pinfo -> cinfo , COL_INFO , "%s, MID:%u, %s" , val_to_str ( ttype , vals_ttype_short , "Unknown %u" ) , mid , val_to_str_ext ( code , & coap_vals_code_ext , "Unknown %u" ) ) ;
 proto_item_append_text ( coap_root , ", %s, %s, MID:%u" , val_to_str ( ttype , vals_ttype , "Unknown %u" ) , val_to_str_ext ( code , & coap_vals_code_ext , "Unknown %u" ) , mid ) ;
 offset += 2 ;
 coinfo -> block_number = DEFAULT_COAP_BLOCK_NUMBER ;
 coinfo -> block_mflag = 0 ;
 coinfo -> uri_str_strbuf = wmem_strbuf_sized_new ( wmem_packet_scope ( ) , 0 , 1024 ) ;
 coinfo -> uri_query_strbuf = wmem_strbuf_sized_new ( wmem_packet_scope ( ) , 0 , 1024 ) ;
 coinfo -> oscore_info = wmem_new0 ( wmem_packet_scope ( ) , oscore_info_t ) ;
 coinfo -> object_security = FALSE ;
 coap_token_str = NULL ;
 if ( token_len > 0 ) {
 coap_token_str = tvb_bytes_to_str_punct ( wmem_file_scope ( ) , tvb , offset , token_len , ' ' ) ;
 proto_tree_add_item ( coap_tree , hf_coap_token , tvb , offset , token_len , ENC_NA ) ;
 offset += token_len ;
 }
 offset = dissect_coap_options ( tvb , pinfo , coap_tree , offset , coap_length , coinfo , & dissect_coap_hf ) ;
 if ( offset == - 1 ) return tvb_captured_length ( tvb ) ;
 conversation = find_or_create_conversation_noaddrb ( pinfo , ( code_class == 0 ) ) ;
 ccinfo = ( coap_conv_info * ) conversation_get_proto_data ( conversation , proto_coap ) ;
 if ( ! ccinfo ) {
 ccinfo = wmem_new ( wmem_file_scope ( ) , coap_conv_info ) ;
 ccinfo -> messages = wmem_map_new ( wmem_file_scope ( ) , g_str_hash , g_str_equal ) ;
 conversation_add_proto_data ( conversation , proto_coap , ccinfo ) ;
 }
 if ( coap_token_str != NULL ) {
 if ( code != 0 ) {
 coap_trans = ( coap_transaction * ) wmem_map_lookup ( ccinfo -> messages , coap_token_str ) ;
 if ( ! coap_trans ) {
 if ( ( ! PINFO_FD_VISITED ( pinfo ) ) && ( code_class == 0 ) ) {
 coap_trans = wmem_new0 ( wmem_file_scope ( ) , coap_transaction ) ;
 coap_trans -> req_frame = pinfo -> num ;
 coap_trans -> rsp_frame = 0 ;
 coap_trans -> req_time = pinfo -> fd -> abs_ts ;
 if ( coinfo -> uri_str_strbuf ) {
 coap_trans -> uri_str_strbuf = wmem_strbuf_new ( wmem_file_scope ( ) , wmem_strbuf_get_str ( coinfo -> uri_str_strbuf ) ) ;
 }
 if ( coinfo -> oscore_info ) {
 coap_trans -> oscore_info = ( oscore_info_t * ) wmem_memdup ( wmem_file_scope ( ) , coinfo -> oscore_info , sizeof ( oscore_info_t ) ) ;
 if ( coinfo -> oscore_info -> kid ) {
 coap_trans -> oscore_info -> kid = ( guint8 * ) wmem_memdup ( wmem_file_scope ( ) , coinfo -> oscore_info -> kid , coinfo -> oscore_info -> kid_len ) ;
 }
 if ( coinfo -> oscore_info -> kid_context ) {
 coap_trans -> oscore_info -> kid_context = ( guint8 * ) wmem_memdup ( wmem_file_scope ( ) , coinfo -> oscore_info -> kid_context , coinfo -> oscore_info -> kid_context_len ) ;
 }
 if ( coinfo -> oscore_info -> piv ) {
 coap_trans -> oscore_info -> piv = ( guint8 * ) wmem_memdup ( wmem_file_scope ( ) , coinfo -> oscore_info -> piv , coinfo -> oscore_info -> piv_len ) ;
 }
 }
 wmem_map_insert ( ccinfo -> messages , coap_token_str , ( void * ) coap_trans ) ;
 }
 }
 else {
 if ( ( code_class >= 2 ) && ( code_class <= 5 ) ) {
 if ( ! PINFO_FD_VISITED ( pinfo ) ) {
 coap_trans -> rsp_frame = pinfo -> num ;
 }
 if ( coap_trans -> uri_str_strbuf ) {
 coinfo -> uri_str_strbuf = wmem_strbuf_new ( wmem_packet_scope ( ) , wmem_strbuf_get_str ( coap_trans -> uri_str_strbuf ) ) ;
 }
 if ( coap_trans -> oscore_info ) {
 if ( coap_trans -> oscore_info -> kid ) {
 coinfo -> oscore_info -> kid = ( guint8 * ) wmem_memdup ( wmem_packet_scope ( ) , coap_trans -> oscore_info -> kid , coap_trans -> oscore_info -> kid_len ) ;
 }
 coinfo -> oscore_info -> kid_len = coap_trans -> oscore_info -> kid_len ;
 if ( coap_trans -> oscore_info -> kid_context ) {
 coinfo -> oscore_info -> kid_context = ( guint8 * ) wmem_memdup ( wmem_packet_scope ( ) , coap_trans -> oscore_info -> kid_context , coap_trans -> oscore_info -> kid_context_len ) ;
 }
 coinfo -> oscore_info -> kid_context_len = coap_trans -> oscore_info -> kid_context_len ;
 if ( coinfo -> oscore_info -> piv_len > 0 ) {
 coinfo -> oscore_info -> piv_in_response = TRUE ;
 coap_trans -> oscore_info -> piv_in_response = TRUE ;
 }
 else if ( coap_trans -> oscore_info -> piv_len > 0 ) {
 coinfo -> oscore_info -> piv = ( guint8 * ) wmem_memdup ( wmem_packet_scope ( ) , coap_trans -> oscore_info -> piv , coap_trans -> oscore_info -> piv_len ) ;
 coinfo -> oscore_info -> piv_len = coap_trans -> oscore_info -> piv_len ;
 }
 coinfo -> oscore_info -> response = TRUE ;
 }
 }
 }
 }
 }
 if ( coap_trans != NULL ) {
 if ( code_class == 0 ) {
 if ( coap_trans -> rsp_frame ) {
 proto_item * it ;
 it = proto_tree_add_uint ( coap_tree , hf_coap_response_in , tvb , 0 , 0 , coap_trans -> rsp_frame ) ;
 PROTO_ITEM_SET_GENERATED ( it ) ;
 }
 }
 else if ( ( code_class >= 2 ) && ( code_class <= 5 ) ) {
 if ( coap_trans -> req_frame ) {
 proto_item * it ;
 nstime_t ns ;
 it = proto_tree_add_uint ( coap_tree , hf_coap_response_to , tvb , 0 , 0 , coap_trans -> req_frame ) ;
 PROTO_ITEM_SET_GENERATED ( it ) ;
 nstime_delta ( & ns , & pinfo -> fd -> abs_ts , & coap_trans -> req_time ) ;
 it = proto_tree_add_time ( coap_tree , hf_coap_response_time , tvb , 0 , 0 , & ns ) ;
 PROTO_ITEM_SET_GENERATED ( it ) ;
 }
 if ( coinfo -> object_security && coap_trans -> oscore_info ) {
 proto_item * it ;
 it = proto_tree_add_bytes ( coap_tree , hf_coap_oscore_kid , tvb , 0 , coap_trans -> oscore_info -> kid_len , coap_trans -> oscore_info -> kid ) ;
 PROTO_ITEM_SET_GENERATED ( it ) ;
 it = proto_tree_add_bytes ( coap_tree , hf_coap_oscore_kid_context , tvb , 0 , coap_trans -> oscore_info -> kid_context_len , coap_trans -> oscore_info -> kid_context ) ;
 PROTO_ITEM_SET_GENERATED ( it ) ;
 if ( coap_trans -> oscore_info -> piv_in_response ) {
 it = proto_tree_add_bytes ( coap_tree , hf_coap_oscore_piv , tvb , 0 , coinfo -> oscore_info -> piv_len , coinfo -> oscore_info -> piv ) ;
 }
 else {
 it = proto_tree_add_bytes ( coap_tree , hf_coap_oscore_piv , tvb , 0 , coap_trans -> oscore_info -> piv_len , coap_trans -> oscore_info -> piv ) ;
 }
 PROTO_ITEM_SET_GENERATED ( it ) ;
 }
 }
 }
 if ( coap_token_str != NULL ) col_append_fstr ( pinfo -> cinfo , COL_INFO , ", TKN:%s" , coap_token_str ) ;
 if ( coinfo -> block_number != DEFAULT_COAP_BLOCK_NUMBER ) col_append_fstr ( pinfo -> cinfo , COL_INFO , ", %sBlock #%u" , coinfo -> block_mflag ? "" : "End of " , coinfo -> block_number ) ;
 if ( wmem_strbuf_get_len ( coinfo -> uri_str_strbuf ) > 0 ) {
 col_append_fstr ( pinfo -> cinfo , COL_INFO , ", %s" , wmem_strbuf_get_str ( coinfo -> uri_str_strbuf ) ) ;
 pi = proto_tree_add_string ( coap_tree , dissect_coap_hf . hf . opt_uri_path_recon , tvb , 0 , 0 , wmem_strbuf_get_str ( coinfo -> uri_str_strbuf ) ) ;
 PROTO_ITEM_SET_GENERATED ( pi ) ;
 }
 if ( wmem_strbuf_get_len ( coinfo -> uri_query_strbuf ) > 0 ) col_append_str ( pinfo -> cinfo , COL_INFO , wmem_strbuf_get_str ( coinfo -> uri_query_strbuf ) ) ;
 if ( coap_length > offset ) {
 dissect_coap_payload ( tvb , pinfo , coap_tree , parent_tree , offset , coap_length , code_class , coinfo , & dissect_coap_hf , FALSE ) ;
 }
 return tvb_captured_length ( tvb ) ;
 }