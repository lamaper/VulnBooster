static void dissect_rsvp_flowspec ( proto_item * ti , packet_info * pinfo , proto_tree * rsvp_object_tree , tvbuff_t * tvb , int offset , int obj_length , int rsvp_class _U_ , int type ) {
 int offset2 = offset + 4 ;
 int mylen , signal_type ;
 proto_tree * flowspec_tree , * ti2 = NULL ;
 proto_tree_add_uint ( rsvp_object_tree , hf_rsvp_ctype , tvb , offset + 3 , 1 , type ) ;
 mylen = obj_length - 4 ;
 switch ( type ) {
 case 2 : if ( mylen < 4 ) {
 proto_tree_add_expert_format ( rsvp_object_tree , pinfo , & ei_rsvp_invalid_length , tvb , 0 , 0 , "Object length %u < 8" , obj_length ) ;
 return ;
 }
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_flowspec_message_format_version , tvb , offset2 , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_uint_format_value ( rsvp_object_tree , hf_rsvp_data_length , tvb , offset2 + 2 , 2 , tvb_get_ntohs ( tvb , offset2 + 2 ) , "%u words, not including header" , tvb_get_ntohs ( tvb , offset2 + 2 ) ) ;
 proto_item_set_text ( ti , "FLOWSPEC: " ) ;
 mylen -= 4 ;
 offset2 += 4 ;
 while ( mylen > 0 ) {
 guint8 service_num ;
 guint length ;
 guint8 param_id ;
 guint param_len , raw_len ;
 guint param_len_processed ;
 if ( mylen < 4 ) {
 proto_tree_add_expert_format ( rsvp_object_tree , pinfo , & ei_rsvp_invalid_length , tvb , 0 , 0 , "Object length %u not large enough" , obj_length ) ;
 return ;
 }
 service_num = tvb_get_guint8 ( tvb , offset2 ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_flowspec_service_header , tvb , offset2 , 1 , ENC_BIG_ENDIAN ) ;
 length = tvb_get_ntohs ( tvb , offset2 + 2 ) ;
 proto_tree_add_uint_format ( rsvp_object_tree , hf_rsvp_data_length , tvb , offset2 + 2 , 2 , length , "Length of service %u data: %u words, not including header" , service_num , length ) ;
 mylen -= 4 ;
 offset2 += 4 ;
 proto_item_append_text ( ti , "%s: " , val_to_str_ext ( service_num , & intsrv_services_str_ext , "Unknown (%d)" ) ) ;
 param_len_processed = 0 ;
 while ( param_len_processed < length ) {
 ti2 = proto_tree_add_item ( rsvp_object_tree , hf_rsvp_parameter , tvb , offset2 , 1 , ENC_NA ) ;
 param_id = tvb_get_guint8 ( tvb , offset2 ) ;
 raw_len = tvb_get_ntohs ( tvb , offset2 + 2 ) ;
 param_len = raw_len + 1 ;
 switch ( param_id ) {
 case 127 : proto_item_set_len ( ti2 , param_len * 4 ) ;
 flowspec_tree = proto_item_add_subtree ( ti2 , TREE ( TT_FLOWSPEC_SUBTREE ) ) ;
 proto_tree_add_item ( flowspec_tree , hf_rsvp_parameter_flags , tvb , offset2 + 1 , 1 , ENC_NA ) ;
 proto_tree_add_uint_format_value ( flowspec_tree , hf_rsvp_parameter_length , tvb , offset2 + 2 , 2 , raw_len , "%u words, not including header" , raw_len ) ;
 proto_tree_add_item ( flowspec_tree , hf_rsvp_flowspec_token_bucket_rate , tvb , offset2 + 4 , 4 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( flowspec_tree , hf_rsvp_flowspec_token_bucket_size , tvb , offset2 + 8 , 4 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( flowspec_tree , hf_rsvp_flowspec_peak_data_rate , tvb , offset2 + 12 , 4 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( flowspec_tree , hf_rsvp_minimum_policed_unit , tvb , offset2 + 16 , 4 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( flowspec_tree , hf_rsvp_maximum_packet_size , tvb , offset2 + 20 , 4 , ENC_BIG_ENDIAN ) ;
 proto_item_append_text ( ti , "Token Bucket, %.10g bytes/sec. " , tvb_get_ntohieee_float ( tvb , offset2 + 4 ) ) ;
 proto_item_append_text ( ti2 , "Rate=%.10g Burst=%.10g Peak=%.10g m=%u M=%u" , tvb_get_ntohieee_float ( tvb , offset2 + 4 ) , tvb_get_ntohieee_float ( tvb , offset2 + 8 ) , tvb_get_ntohieee_float ( tvb , offset2 + 12 ) , tvb_get_ntohl ( tvb , offset2 + 16 ) , tvb_get_ntohl ( tvb , offset2 + 20 ) ) ;
 break ;
 case 130 : proto_item_set_len ( ti2 , param_len * 4 ) ;
 flowspec_tree = proto_item_add_subtree ( ti2 , TREE ( TT_FLOWSPEC_SUBTREE ) ) ;
 proto_tree_add_item ( flowspec_tree , hf_rsvp_parameter_flags , tvb , offset2 + 1 , 1 , ENC_NA ) ;
 proto_tree_add_uint_format_value ( flowspec_tree , hf_rsvp_parameter_length , tvb , offset2 + 2 , 2 , raw_len , "%u words, not including header" , raw_len ) ;
 proto_tree_add_item ( flowspec_tree , hf_rsvp_flowspec_rate , tvb , offset2 + 4 , 4 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( flowspec_tree , hf_rsvp_flowspec_slack_term , tvb , offset2 + 8 , 4 , ENC_BIG_ENDIAN ) ;
 proto_item_append_text ( ti , "RSpec, %.10g bytes/sec. " , tvb_get_ntohieee_float ( tvb , offset2 + 4 ) ) ;
 proto_item_append_text ( ti2 , "R=%.10g, s=%u" , tvb_get_ntohieee_float ( tvb , offset2 + 4 ) , tvb_get_ntohl ( tvb , offset2 + 8 ) ) ;
 break ;
 case 128 : proto_item_set_len ( ti2 , param_len * 4 ) ;
 flowspec_tree = proto_item_add_subtree ( ti2 , TREE ( TT_FLOWSPEC_SUBTREE ) ) ;
 proto_tree_add_item ( flowspec_tree , hf_rsvp_parameter_flags , tvb , offset2 + 1 , 1 , ENC_NA ) ;
 proto_tree_add_uint_format_value ( flowspec_tree , hf_rsvp_parameter_length , tvb , offset2 + 2 , 2 , raw_len , "%u words, not including header" , raw_len ) ;
 proto_tree_add_item ( flowspec_tree , hf_rsvp_maximum_packet_size , tvb , offset2 + 4 , 4 , ENC_BIG_ENDIAN ) ;
 proto_item_append_text ( ti , "Null Service. M=%u" , tvb_get_ntohl ( tvb , offset2 + 4 ) ) ;
 proto_item_append_text ( ti2 , "Max pkt size=%u" , tvb_get_ntohl ( tvb , offset2 + 4 ) ) ;
 break ;
 default : expert_add_info_format ( pinfo , ti2 , & ei_rsvp_parameter , "Unknown parameter %d, %d words" , param_id , param_len ) ;
 break ;
 }
 param_len_processed += param_len ;
 offset2 += param_len * 4 ;
 }
 mylen -= length * 4 ;
 }
 break ;
 case 4 : proto_item_set_text ( ti , "FLOWSPEC: SONET/SDH, " ) ;
 proto_tree_add_uint_format_value ( rsvp_object_tree , hf_rsvp_ctype , tvb , offset + 3 , 1 , type , "4 - SONET/SDH" ) ;
 signal_type = tvb_get_guint8 ( tvb , offset2 ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_flowspec_signal_type_sonet , tvb , offset2 , 1 , ENC_BIG_ENDIAN ) ;
 ti2 = proto_tree_add_item ( rsvp_object_tree , hf_rsvp_flowspec_requested_concatenation , tvb , offset2 + 1 , 1 , ENC_BIG_ENDIAN ) ;
 flowspec_tree = proto_item_add_subtree ( ti2 , TREE ( TT_FLOWSPEC_SUBTREE ) ) ;
 proto_tree_add_item ( flowspec_tree , hf_rsvp_flowspec_standard_contiguous_concatenation , tvb , offset2 + 1 , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( flowspec_tree , hf_rsvp_flowspec_arbitrary_contiguous_concatenation , tvb , offset2 + 1 , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_flowspec_number_of_contiguous_components , tvb , offset2 + 2 , 2 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_flowspec_number_of_virtual_components , tvb , offset2 + 4 , 2 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_flowspec_multiplier , tvb , offset2 + 6 , 2 , ENC_BIG_ENDIAN ) ;
 ti2 = proto_tree_add_item ( rsvp_object_tree , hf_rsvp_flowspec_transparency , tvb , offset2 + 8 , 4 , ENC_BIG_ENDIAN ) ;
 flowspec_tree = proto_item_add_subtree ( ti2 , TREE ( TT_FLOWSPEC_SUBTREE ) ) ;
 proto_tree_add_item ( flowspec_tree , hf_rsvp_flowspec_regenerator_section , tvb , offset2 + 8 , 4 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( flowspec_tree , hf_rsvp_flowspec_multiplex_section , tvb , offset2 + 8 , 4 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( flowspec_tree , hf_rsvp_flowspec_J0_transparency , tvb , offset2 + 8 , 4 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( flowspec_tree , hf_rsvp_flowspec_SOH_RSOH_DCC_transparency , tvb , offset2 + 8 , 4 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( flowspec_tree , hf_rsvp_flowspec_LOH_MSOH_DCC_transparency , tvb , offset2 + 8 , 4 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( flowspec_tree , hf_rsvp_flowspec_LOH_MSOH_extended_DCC_transparency , tvb , offset2 + 8 , 4 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( flowspec_tree , hf_rsvp_flowspec_K1_K2_transparency , tvb , offset2 + 8 , 4 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( flowspec_tree , hf_rsvp_flowspec_E1_transparency , tvb , offset2 + 8 , 4 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( flowspec_tree , hf_rsvp_flowspec_F1_transparency , tvb , offset2 + 8 , 4 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( flowspec_tree , hf_rsvp_flowspec_E2_transparency , tvb , offset2 + 8 , 4 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( flowspec_tree , hf_rsvp_flowspec_B1_transparency , tvb , offset2 + 8 , 4 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( flowspec_tree , hf_rsvp_flowspec_B2_transparency , tvb , offset2 + 8 , 4 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( flowspec_tree , hf_rsvp_flowspec_M0_transparency , tvb , offset2 + 8 , 4 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( flowspec_tree , hf_rsvp_flowspec_M1_transparency , tvb , offset2 + 8 , 4 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_flowspec_profile , tvb , offset2 + 12 , 4 , ENC_BIG_ENDIAN ) ;
 proto_item_append_text ( ti , "Signal [%s], RCC %d, NCC %d, NVC %d, MT %d, Transparency %d, Profile %d" , val_to_str_ext_const ( signal_type , & gmpls_sonet_signal_type_str_ext , "Unknown" ) , tvb_get_guint8 ( tvb , offset2 + 1 ) , tvb_get_ntohs ( tvb , offset2 + 2 ) , tvb_get_ntohs ( tvb , offset2 + 4 ) , tvb_get_ntohs ( tvb , offset2 + 6 ) , tvb_get_ntohl ( tvb , offset2 + 8 ) , tvb_get_ntohl ( tvb , offset2 + 12 ) ) ;
 break ;
 case 5 : proto_item_set_text ( ti , "FLOWSPEC: G.709, " ) ;
 proto_tree_add_uint_format_value ( rsvp_object_tree , hf_rsvp_ctype , tvb , offset + 3 , 1 , type , "5 - G.709" ) ;
 signal_type = tvb_get_guint8 ( tvb , offset2 ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_flowspec_signal_type_g709 , tvb , offset2 , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_flowspec_number_of_multiplexed_components , tvb , offset2 + 2 , 2 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_flowspec_number_of_virtual_components , tvb , offset2 + 4 , 2 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_flowspec_multiplier , tvb , offset2 + 6 , 2 , ENC_BIG_ENDIAN ) ;
 proto_item_append_text ( ti , "Signal [%s], NMC %d, NVC %d, MT %d" , rval_to_str ( signal_type , gmpls_g709_signal_type_rvals , "Unknown" ) , tvb_get_ntohs ( tvb , offset2 + 2 ) , tvb_get_ntohs ( tvb , offset2 + 4 ) , tvb_get_ntohs ( tvb , offset2 + 6 ) ) ;
 break ;
 case 6 : proto_item_set_text ( ti , "FLOWSPEC: Ethernet, " ) ;
 proto_tree_add_uint_format_value ( rsvp_object_tree , hf_rsvp_ctype , tvb , offset + 3 , 1 , type , "6 - Ethernet" ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_switching_granularity , tvb , offset2 , 2 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_flowspec_mtu , tvb , offset2 + 2 , 2 , ENC_BIG_ENDIAN ) ;
 dissect_rsvp_eth_tspec_tlv ( ti , pinfo , rsvp_object_tree , tvb , offset + 8 , obj_length - 8 , TREE ( TT_FLOWSPEC_SUBTREE ) ) ;
 break ;
 default : break ;
 }
 }