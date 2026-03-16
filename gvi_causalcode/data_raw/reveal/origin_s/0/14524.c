static void dissect_rsvp_adspec ( proto_item * ti _U_ , packet_info * pinfo , proto_tree * rsvp_object_tree , tvbuff_t * tvb , int offset , int obj_length , int rsvp_class _U_ , int type ) {
 int offset2 = offset + 4 ;
 int mylen , i ;
 proto_tree * adspec_tree , * adspec_type_tree ;
 proto_item * ti2 ;
 proto_tree_add_uint ( rsvp_object_tree , hf_rsvp_ctype , tvb , offset + 3 , 1 , type ) ;
 mylen = obj_length - 4 ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_adspec_message_format_version , tvb , offset2 , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_uint_format_value ( rsvp_object_tree , hf_rsvp_data_length , tvb , offset2 + 2 , 2 , tvb_get_ntohs ( tvb , offset2 + 2 ) , "%u words, not including header" , tvb_get_ntohs ( tvb , offset2 + 2 ) ) ;
 mylen -= 4 ;
 offset2 += 4 ;
 while ( mylen > 0 ) {
 guint8 service_num ;
 guint length ;
 const char * str ;
 service_num = tvb_get_guint8 ( tvb , offset2 ) ;
 str = val_to_str_ext_const ( service_num , & intsrv_services_str_ext , "Unknown" ) ;
 length = tvb_get_ntohs ( tvb , offset2 + 2 ) ;
 adspec_tree = proto_tree_add_subtree ( rsvp_object_tree , tvb , offset2 , ( length + 1 ) * 4 , TREE ( TT_ADSPEC_SUBTREE ) , NULL , str ) ;
 proto_tree_add_item ( adspec_tree , hf_rsvp_adspec_service_header , tvb , offset2 , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( adspec_tree , hf_rsvp_hf_rsvp_adspec_break_bit , tvb , offset2 + 1 , 1 , ENC_NA ) ;
 proto_tree_add_uint_format_value ( adspec_tree , hf_rsvp_data_length , tvb , offset2 + 2 , 2 , length , "%u words, not including header" , length ) ;
 mylen -= 4 ;
 offset2 += 4 ;
 i = length * 4 ;
 while ( i > 0 ) {
 guint id , phdr_length ;
 ti2 = proto_tree_add_item_ret_uint ( adspec_tree , hf_rsvp_adspec_type , tvb , offset2 , 1 , ENC_NA , & id ) ;
 adspec_type_tree = proto_item_add_subtree ( ti2 , TREE ( TT_ADSPEC_TYPE_SUBTREE ) ) ;
 proto_tree_add_item_ret_uint ( adspec_type_tree , hf_rsvp_adspec_len , tvb , offset2 + 2 , 2 , ENC_BIG_ENDIAN , & phdr_length ) ;
 proto_item_set_len ( ti2 , phdr_length ) ;
 str = try_val_to_str_ext ( id , & adspec_params_ext ) ;
 if ( str ) {
 switch ( id ) {
 case 4 : case 8 : case 10 : case 133 : case 134 : case 135 : case 136 : proto_tree_add_uint_format ( adspec_type_tree , hf_rsvp_adspec_uint , tvb , offset2 , ( phdr_length + 1 ) << 2 , tvb_get_ntohl ( tvb , offset2 + 4 ) , "%s: %u" , str , tvb_get_ntohl ( tvb , offset2 + 4 ) ) ;
 break ;
 case 6 : proto_tree_add_float_format ( adspec_type_tree , hf_rsvp_adspec_float , tvb , offset2 , ( phdr_length + 1 ) << 2 , tvb_get_ntohieee_float ( tvb , offset2 + 4 ) , "%s: %.10g" , str , tvb_get_ntohieee_float ( tvb , offset2 + 4 ) ) ;
 break ;
 default : proto_tree_add_bytes_format ( adspec_tree , hf_rsvp_adspec_bytes , tvb , offset2 , ( phdr_length + 1 ) << 2 , NULL , "%s" , str ) ;
 break ;
 }
 }
 else {
 expert_add_info ( pinfo , ti2 , & ei_rsvp_adspec_type ) ;
 }
 offset2 += ( phdr_length + 1 ) << 2 ;
 i -= ( phdr_length + 1 ) << 2 ;
 mylen -= ( phdr_length + 1 ) << 2 ;
 }
 }
 }