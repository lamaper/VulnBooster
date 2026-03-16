static int dissect_diameter_common ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , void * data _U_ ) {
 guint32 first_word = tvb_get_ntohl ( tvb , 0 ) ;
 guint32 version = ( first_word & 0xff000000 ) >> 24 ;
 guint32 flags_bits = ( tvb_get_ntohl ( tvb , 4 ) & 0xff000000 ) >> 24 ;
 int packet_len = first_word & 0x00ffffff ;
 proto_item * pi , * cmd_item , * app_item , * version_item ;
 proto_tree * diam_tree ;
 diam_ctx_t * c = ( diam_ctx_t * ) wmem_alloc0 ( wmem_packet_scope ( ) , sizeof ( diam_ctx_t ) ) ;
 int offset ;
 value_string * cmd_vs ;
 const char * cmd_str ;
 guint32 cmd = tvb_get_ntoh24 ( tvb , 5 ) ;
 guint32 hop_by_hop_id , end_to_end_id ;
 conversation_t * conversation ;
 diameter_conv_info_t * diameter_conv_info ;
 diameter_req_ans_pair_t * diameter_pair = NULL ;
 wmem_tree_t * pdus_tree ;
 proto_item * it ;
 nstime_t ns ;
 diam_sub_dis_t * diam_sub_dis_inf = wmem_new0 ( wmem_packet_scope ( ) , diam_sub_dis_t ) ;
 diam_sub_dis_inf -> application_id = tvb_get_ntohl ( tvb , 8 ) ;
 col_set_str ( pinfo -> cinfo , COL_PROTOCOL , "DIAMETER" ) ;
 pi = proto_tree_add_item ( tree , proto_diameter , tvb , 0 , - 1 , ENC_NA ) ;
 diam_tree = proto_item_add_subtree ( pi , ett_diameter ) ;
 c -> tree = diam_tree ;
 c -> pinfo = pinfo ;
 version_item = proto_tree_add_item ( diam_tree , hf_diameter_version , tvb , 0 , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( diam_tree , hf_diameter_length , tvb , 1 , 3 , ENC_BIG_ENDIAN ) ;
 pi = proto_tree_add_bitmask ( diam_tree , tvb , 4 , hf_diameter_flags , ett_diameter_flags , diameter_flags_fields , ENC_BIG_ENDIAN ) ;
 if ( flags_bits & 0x0f ) expert_add_info ( c -> pinfo , pi , & ei_diameter_reserved_bit_set ) ;
 cmd_item = proto_tree_add_item ( diam_tree , hf_diameter_code , tvb , 5 , 3 , ENC_BIG_ENDIAN ) ;
 switch ( version ) {
 case DIAMETER_V16 : {
 guint32 vendorid = tvb_get_ntohl ( tvb , 8 ) ;
 diam_vnd_t * vendor ;
 if ( ! ( vendor = ( diam_vnd_t * ) wmem_tree_lookup32 ( dictionary . vnds , vendorid ) ) ) {
 vendor = & unknown_vendor ;
 }
 cmd_vs = VND_CMD_VS ( vendor ) ;
 proto_tree_add_item ( diam_tree , hf_diameter_vendor_id , tvb , 8 , 4 , ENC_BIG_ENDIAN ) ;
 c -> version_rfc = FALSE ;
 break ;
 }
 case DIAMETER_RFC : {
 cmd_vs = ( value_string * ) ( void * ) all_cmds -> data ;
 app_item = proto_tree_add_item ( diam_tree , hf_diameter_application_id , tvb , 8 , 4 , ENC_BIG_ENDIAN ) ;
 if ( try_val_to_str_ext ( diam_sub_dis_inf -> application_id , dictionary . applications ) == NULL ) {
 proto_tree * tu = proto_item_add_subtree ( app_item , ett_unknown ) ;
 proto_tree_add_expert_format ( tu , c -> pinfo , & ei_diameter_application_id , tvb , 8 , 4 , "Unknown Application Id (%u), if you know what this is you can add it to dictionary.xml" , diam_sub_dis_inf -> application_id ) ;
 }
 c -> version_rfc = TRUE ;
 break ;
 }
 default : {
 proto_tree * pt = proto_item_add_subtree ( version_item , ett_err ) ;
 proto_tree_add_expert ( pt , pinfo , & ei_diameter_version , tvb , 0 , 1 ) ;
 c -> version_rfc = TRUE ;
 cmd_vs = VND_CMD_VS ( & no_vnd ) ;
 break ;
 }
 }
 cmd_str = val_to_str_const ( cmd , cmd_vs , "Unknown" ) ;
 col_add_fstr ( pinfo -> cinfo , COL_INFO , "cmd=%s%s(%d) flags=%s %s=%s(%d) h2h=%x e2e=%x" , cmd_str , ( ( flags_bits >> 4 ) & 0x08 ) ? " Request" : " Answer" , cmd , msgflags_str [ ( ( flags_bits >> 4 ) & 0x0f ) ] , c -> version_rfc ? "appl" : "vend" , c -> version_rfc ? val_to_str_ext_const ( diam_sub_dis_inf -> application_id , dictionary . applications , "Unknown" ) : val_to_str_const ( diam_sub_dis_inf -> application_id , vnd_short_vs , "Unknown" ) , diam_sub_dis_inf -> application_id , tvb_get_ntohl ( tvb , 12 ) , tvb_get_ntohl ( tvb , 16 ) ) ;
 col_append_str ( pinfo -> cinfo , COL_INFO , " | " ) ;
 col_set_fence ( pinfo -> cinfo , COL_INFO ) ;
 proto_item_append_text ( cmd_item , " %s" , cmd_str ) ;
 if ( strcmp ( cmd_str , "Unknown" ) == 0 ) {
 proto_tree * tu = proto_item_add_subtree ( cmd_item , ett_unknown ) ;
 proto_tree_add_expert ( tu , c -> pinfo , & ei_diameter_code , tvb , 5 , 3 ) ;
 }
 hop_by_hop_id = tvb_get_ntohl ( tvb , 12 ) ;
 proto_tree_add_item ( diam_tree , hf_diameter_hopbyhopid , tvb , 12 , 4 , ENC_BIG_ENDIAN ) ;
 end_to_end_id = tvb_get_ntohl ( tvb , 16 ) ;
 proto_tree_add_item ( diam_tree , hf_diameter_endtoendid , tvb , 16 , 4 , ENC_BIG_ENDIAN ) ;
 conversation = find_or_create_conversation ( pinfo ) ;
 diameter_conv_info = ( diameter_conv_info_t * ) conversation_get_proto_data ( conversation , proto_diameter ) ;
 if ( ! diameter_conv_info ) {
 diameter_conv_info = wmem_new ( wmem_file_scope ( ) , diameter_conv_info_t ) ;
 diameter_conv_info -> pdus_tree = wmem_map_new ( wmem_file_scope ( ) , g_direct_hash , g_direct_equal ) ;
 conversation_add_proto_data ( conversation , proto_diameter , diameter_conv_info ) ;
 }
 pdus_tree = ( wmem_tree_t * ) wmem_map_lookup ( diameter_conv_info -> pdus_tree , GUINT_TO_POINTER ( hop_by_hop_id ) ) ;
 if ( pdus_tree == NULL && ( flags_bits & DIAM_FLAGS_R ) ) {
 pdus_tree = wmem_tree_new ( wmem_file_scope ( ) ) ;
 wmem_map_insert ( diameter_conv_info -> pdus_tree , GUINT_TO_POINTER ( hop_by_hop_id ) , pdus_tree ) ;
 }
 if ( pdus_tree ) {
 if ( ! pinfo -> fd -> flags . visited ) {
 if ( flags_bits & DIAM_FLAGS_R ) {
 diameter_pair = wmem_new ( wmem_file_scope ( ) , diameter_req_ans_pair_t ) ;
 diameter_pair -> hop_by_hop_id = hop_by_hop_id ;
 diameter_pair -> end_to_end_id = end_to_end_id ;
 diameter_pair -> cmd_code = cmd ;
 diameter_pair -> result_code = 0 ;
 diameter_pair -> cmd_str = cmd_str ;
 diameter_pair -> req_frame = PINFO_FD_NUM ( pinfo ) ;
 diameter_pair -> ans_frame = 0 ;
 diameter_pair -> req_time = pinfo -> fd -> abs_ts ;
 wmem_tree_insert32 ( pdus_tree , PINFO_FD_NUM ( pinfo ) , ( void * ) diameter_pair ) ;
 }
 else {
 diameter_pair = ( diameter_req_ans_pair_t * ) wmem_tree_lookup32_le ( pdus_tree , PINFO_FD_NUM ( pinfo ) ) ;
 if ( diameter_pair && diameter_pair -> end_to_end_id == end_to_end_id ) {
 diameter_pair -> ans_frame = PINFO_FD_NUM ( pinfo ) ;
 }
 }
 }
 else {
 diameter_pair = ( diameter_req_ans_pair_t * ) wmem_tree_lookup32_le ( pdus_tree , PINFO_FD_NUM ( pinfo ) ) ;
 if ( diameter_pair && diameter_pair -> end_to_end_id != end_to_end_id ) diameter_pair = NULL ;
 }
 }
 if ( ! diameter_pair ) {
 diameter_pair = ( diameter_req_ans_pair_t * ) wmem_alloc ( wmem_packet_scope ( ) , sizeof ( diameter_req_ans_pair_t ) ) ;
 diameter_pair -> hop_by_hop_id = hop_by_hop_id ;
 diameter_pair -> cmd_code = cmd ;
 diameter_pair -> result_code = 0 ;
 diameter_pair -> cmd_str = cmd_str ;
 diameter_pair -> req_frame = 0 ;
 diameter_pair -> ans_frame = 0 ;
 diameter_pair -> req_time = pinfo -> fd -> abs_ts ;
 }
 diameter_pair -> processing_request = ( flags_bits & DIAM_FLAGS_R ) != 0 ;
 if ( flags_bits & DIAM_FLAGS_R ) {
 if ( diameter_pair -> ans_frame ) {
 it = proto_tree_add_uint ( diam_tree , hf_diameter_answer_in , tvb , 0 , 0 , diameter_pair -> ans_frame ) ;
 PROTO_ITEM_SET_GENERATED ( it ) ;
 }
 }
 else {
 if ( diameter_pair -> req_frame ) {
 it = proto_tree_add_uint ( diam_tree , hf_diameter_answer_to , tvb , 0 , 0 , diameter_pair -> req_frame ) ;
 PROTO_ITEM_SET_GENERATED ( it ) ;
 nstime_delta ( & ns , & pinfo -> fd -> abs_ts , & diameter_pair -> req_time ) ;
 diameter_pair -> srt_time = ns ;
 it = proto_tree_add_time ( diam_tree , hf_diameter_answer_time , tvb , 0 , 0 , & ns ) ;
 PROTO_ITEM_SET_GENERATED ( it ) ;
 }
 }
 offset = 20 ;
 while ( offset < packet_len ) {
 offset += dissect_diameter_avp ( c , tvb , offset , diam_sub_dis_inf ) ;
 }
 tap_queue_packet ( diameter_tap , pinfo , diameter_pair ) ;
 if ( have_tap_listener ( exported_pdu_tap ) ) {
 export_diameter_pdu ( pinfo , tvb ) ;
 }
 return tvb_reported_length ( tvb ) ;
 }