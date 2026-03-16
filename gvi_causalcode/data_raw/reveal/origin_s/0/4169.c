static int dissect_diameter_avp ( diam_ctx_t * c , tvbuff_t * tvb , int offset , diam_sub_dis_t * diam_sub_dis_inf ) {
 guint32 code = tvb_get_ntohl ( tvb , offset ) ;
 guint32 len = tvb_get_ntohl ( tvb , offset + 4 ) ;
 guint32 vendor_flag = len & 0x80000000 ;
 guint32 flags_bits_idx = ( len & 0xE0000000 ) >> 29 ;
 guint32 flags_bits = ( len & 0xFF000000 ) >> 24 ;
 guint32 vendorid = vendor_flag ? tvb_get_ntohl ( tvb , offset + 8 ) : 0 ;
 wmem_tree_key_t k [ 3 ] ;
 diam_avp_t * a ;
 proto_item * pi , * avp_item ;
 proto_tree * avp_tree , * save_tree ;
 tvbuff_t * subtvb ;
 diam_vnd_t * vendor ;
 const char * code_str ;
 const char * avp_str = NULL ;
 guint8 pad_len ;
 k [ 0 ] . length = 1 ;
 k [ 0 ] . key = & code ;
 k [ 1 ] . length = 1 ;
 k [ 1 ] . key = & vendorid ;
 k [ 2 ] . length = 0 ;
 k [ 2 ] . key = NULL ;
 a = ( diam_avp_t * ) wmem_tree_lookup32_array ( dictionary . avps , k ) ;
 len &= 0x00ffffff ;
 pad_len = ( len % 4 ) ? 4 - ( len % 4 ) : 0 ;
 if ( ! a ) {
 a = & unknown_avp ;
 if ( vendor_flag ) {
 if ( ! ( vendor = ( diam_vnd_t * ) wmem_tree_lookup32 ( dictionary . vnds , vendorid ) ) ) vendor = & unknown_vendor ;
 }
 else {
 vendor = & no_vnd ;
 }
 }
 else {
 vendor = ( diam_vnd_t * ) a -> vendor ;
 }
 if ( vendor -> vs_avps_ext == NULL ) {
 g_array_sort ( vendor -> vs_avps , compare_avps ) ;
 vendor -> vs_avps_ext = value_string_ext_new ( VND_AVP_VS ( vendor ) , VND_AVP_VS_LEN ( vendor ) + 1 , g_strdup_printf ( "diameter_vendor_%s" , val_to_str_ext_const ( vendorid , & sminmpec_values_ext , "Unknown" ) ) ) ;

 value_string * vendor_avp_vs = VALUE_STRING_EXT_VS_P ( vendor -> vs_avps_ext ) ;
 gint i = 0 ;
 while ( vendor_avp_vs [ i ] . strptr != NULL ) {
 g_warning ( "%u %s" , vendor_avp_vs [ i ] . value , vendor_avp_vs [ i ] . strptr ) ;
 i ++ ;
 }
 }

 avp_item = proto_tree_add_item ( c -> tree , hf_diameter_avp , tvb , offset , len + pad_len , ENC_NA ) ;
 avp_tree = proto_item_add_subtree ( avp_item , a -> ett ) ;
 pi = proto_tree_add_item ( avp_tree , hf_diameter_avp_code , tvb , offset , 4 , ENC_BIG_ENDIAN ) ;
 code_str = val_to_str_ext_const ( code , vendor -> vs_avps_ext , "Unknown" ) ;
 proto_item_append_text ( pi , " %s" , code_str ) ;
 if ( a == & unknown_avp ) {
 proto_tree * tu = proto_item_add_subtree ( pi , ett_unknown ) ;
 proto_tree_add_expert_format ( tu , c -> pinfo , & ei_diameter_avp_code , tvb , offset , 4 , "Unknown AVP %u (vendor=%s), if you know what this is you can add it to dictionary.xml" , code , val_to_str_ext_const ( vendorid , & sminmpec_values_ext , "Unknown" ) ) ;
 }
 offset += 4 ;
 proto_item_set_text ( avp_item , "AVP: %s(%u) l=%u f=%s" , code_str , code , len , avpflags_str [ flags_bits_idx ] ) ;
 pi = proto_tree_add_item ( avp_tree , hf_diameter_avp_flags , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 {
 proto_tree * flags_tree = proto_item_add_subtree ( pi , ett_diameter_avp_flags ) ;
 proto_tree_add_item ( flags_tree , hf_diameter_avp_flags_vendor_specific , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( flags_tree , hf_diameter_avp_flags_mandatory , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( flags_tree , hf_diameter_avp_flags_protected , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 pi = proto_tree_add_item ( flags_tree , hf_diameter_avp_flags_reserved3 , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 if ( flags_bits & 0x10 ) expert_add_info ( c -> pinfo , pi , & ei_diameter_reserved_bit_set ) ;
 pi = proto_tree_add_item ( flags_tree , hf_diameter_avp_flags_reserved4 , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 if ( flags_bits & 0x08 ) expert_add_info ( c -> pinfo , pi , & ei_diameter_reserved_bit_set ) ;
 pi = proto_tree_add_item ( flags_tree , hf_diameter_avp_flags_reserved5 , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 if ( flags_bits & 0x04 ) expert_add_info ( c -> pinfo , pi , & ei_diameter_reserved_bit_set ) ;
 proto_tree_add_item ( flags_tree , hf_diameter_avp_flags_reserved6 , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 if ( flags_bits & 0x02 ) expert_add_info ( c -> pinfo , pi , & ei_diameter_reserved_bit_set ) ;
 proto_tree_add_item ( flags_tree , hf_diameter_avp_flags_reserved7 , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 if ( flags_bits & 0x01 ) expert_add_info ( c -> pinfo , pi , & ei_diameter_reserved_bit_set ) ;
 }
 offset += 1 ;
 proto_tree_add_item ( avp_tree , hf_diameter_avp_len , tvb , offset , 3 , ENC_BIG_ENDIAN ) ;
 offset += 3 ;
 if ( vendor_flag ) {
 proto_item_append_text ( avp_item , " vnd=%s" , val_to_str ( vendorid , vnd_short_vs , "%d" ) ) ;
 pi = proto_tree_add_item ( avp_tree , hf_diameter_avp_vendor_id , tvb , offset , 4 , ENC_BIG_ENDIAN ) ;
 if ( vendor == & unknown_vendor ) {
 proto_tree * tu = proto_item_add_subtree ( pi , ett_unknown ) ;
 proto_tree_add_expert ( tu , c -> pinfo , & ei_diameter_avp_vendor_id , tvb , offset , 4 ) ;
 }
 offset += 4 ;
 }
 if ( len == ( guint32 ) ( vendor_flag ? 12 : 8 ) ) {
 proto_tree_add_expert ( avp_tree , c -> pinfo , & ei_diameter_avp_no_data , tvb , offset , 0 ) ;
 return len + pad_len ;
 }
 if ( ( diam_sub_dis_inf -> dis_gouped ) && ( ! vendor_flag ) && ( code == 266 ) ) {
 diam_sub_dis_inf -> vendor_id = tvb_get_ntohl ( tvb , offset ) ;
 }
 subtvb = tvb_new_subset_length ( tvb , offset , len - ( 8 + ( vendor_flag ? 4 : 0 ) ) ) ;
 offset += len - ( 8 + ( vendor_flag ? 4 : 0 ) ) ;
 save_tree = c -> tree ;
 c -> tree = avp_tree ;
 if ( ( diam_sub_dis_inf -> dis_gouped ) && ( ! vendor_flag ) && ( code == 298 ) && ( diam_sub_dis_inf -> vendor_id != 0 ) && ( diam_sub_dis_inf -> vendor_id != VENDOR_THE3GPP ) ) {
 if ( ! dissector_try_uint_new ( diameter_expr_result_vnd_table , diam_sub_dis_inf -> vendor_id , subtvb , c -> pinfo , avp_tree , FALSE , diam_sub_dis_inf ) ) {
 dissect_diameter_other_vendor_exp_res ( subtvb , avp_tree , diam_sub_dis_inf ) ;
 }
 if ( diam_sub_dis_inf -> avp_str ) {
 proto_item_append_text ( avp_item , " val=%s" , diam_sub_dis_inf -> avp_str ) ;
 }
 }
 else if ( c -> version_rfc ) {
 avp_str = a -> dissector_rfc ( c , a , subtvb , diam_sub_dis_inf ) ;
 }
 else {
 avp_str = a -> dissector_v16 ( c , a , subtvb , diam_sub_dis_inf ) ;
 }
 c -> tree = save_tree ;
 diam_sub_dis_inf -> avp_str = NULL ;
 call_avp_subdissector ( vendorid , code , subtvb , c -> pinfo , avp_tree , diam_sub_dis_inf ) ;
 if ( diam_sub_dis_inf -> avp_str ) {
 proto_item_append_text ( avp_item , " val=%s" , diam_sub_dis_inf -> avp_str ) ;
 }
 else if ( avp_str ) {
 proto_item_append_text ( avp_item , " val=%s" , avp_str ) ;
 }
 if ( pad_len ) {
 guint8 i ;
 pi = proto_tree_add_item ( avp_tree , hf_diameter_avp_pad , tvb , offset , pad_len , ENC_NA ) ;
 for ( i = 0 ;
 i < pad_len ;
 i ++ ) {
 if ( tvb_get_guint8 ( tvb , offset ++ ) != 0 ) {
 expert_add_info ( c -> pinfo , pi , & ei_diameter_avp_pad ) ;
 break ;
 }
 }
 }
 return len + pad_len ;
 }