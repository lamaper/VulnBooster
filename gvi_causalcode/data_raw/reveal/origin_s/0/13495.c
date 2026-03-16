int dissect_ber_null ( gboolean implicit_tag , asn1_ctx_t * actx , proto_tree * tree , tvbuff_t * tvb , int offset , gint hf_id ) {
 gint8 ber_class ;
 gboolean pc ;
 gint32 tag ;
 guint32 len ;
 int offset_old ;
 proto_item * cause ;
 if ( ! implicit_tag ) {
 offset_old = offset ;
 offset = dissect_ber_identifier ( actx -> pinfo , tree , tvb , offset , & ber_class , & pc , & tag ) ;
 if ( pc || ( ! implicit_tag && ( ( ber_class != BER_CLASS_UNI ) || ( tag != BER_UNI_TAG_NULL ) ) ) ) {
 cause = proto_tree_add_string_format_value ( tree , hf_ber_error , tvb , offset_old , offset - offset_old , "null_expected" , "NULL expected but class:%s(%d) %s tag:%d was unexpected" , val_to_str_const ( ber_class , ber_class_codes , "Unknown" ) , ber_class , pc ? ber_pc_codes_short . true_string : ber_pc_codes_short . false_string , tag ) ;
 expert_add_info ( actx -> pinfo , cause , & ei_ber_expected_null ) ;
 }
 offset_old = offset ;
 offset = dissect_ber_length ( actx -> pinfo , tree , tvb , offset , & len , NULL ) ;
 if ( len ) {
 proto_tree_add_string_format_value ( tree , hf_ber_error , tvb , offset_old , offset - offset_old , "illegal_length" , "NULL expect zero length but Length=%d" , len ) ;
 cause = proto_tree_add_string_format_value ( tree , hf_ber_error , tvb , offset , len , "unexpected_data" , "unexpected data in NULL type" ) ;
 expert_add_info ( actx -> pinfo , cause , & ei_ber_expected_null_zero_length ) ;
 offset += len ;
 }
 }
 if ( hf_id >= 0 ) proto_tree_add_item ( tree , hf_id , tvb , offset , 0 , ENC_BIG_ENDIAN ) ;
 return offset ;
 }