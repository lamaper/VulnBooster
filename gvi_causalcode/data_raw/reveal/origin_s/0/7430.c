int dissect_ber_constrained_restricted_string ( gboolean implicit_tag , gint32 type , asn1_ctx_t * actx , proto_tree * tree , tvbuff_t * tvb , int offset , gint32 min_len , gint32 max_len , gint hf_id , tvbuff_t * * out_tvb ) {
 gint8 ber_class ;
 gboolean pc ;
 gint32 tag ;
 guint32 len ;
 int eoffset ;
 int hoffset = offset ;
 proto_item * cause ;

 const char * name ;
 header_field_info * hfinfo ;
 if ( hf_id >= 0 ) {
 hfinfo = proto_registrar_get_nth ( hf_id ) ;
 name = hfinfo -> name ;
 }
 else {
 name = "unnamed" ;
 }
 if ( tvb_reported_length_remaining ( tvb , offset ) > 3 ) {
 printf ( "RESTRICTED STRING dissect_ber_octet string(%s) entered implicit_tag:%d offset:%d len:%d %02x:%02x:%02x\n" , name , implicit_tag , offset , tvb_reported_length_remaining ( tvb , offset ) , tvb_get_guint8 ( tvb , offset ) , tvb_get_guint8 ( tvb , offset + 1 ) , tvb_get_guint8 ( tvb , offset + 2 ) ) ;
 }
 else {
 printf ( "RESTRICTED STRING dissect_ber_octet_string(%s) entered\n" , name ) ;
 }
 }

 offset = get_ber_identifier ( tvb , offset , & ber_class , & pc , & tag ) ;
 offset = get_ber_length ( tvb , offset , & len , NULL ) ;
 eoffset = offset + len ;
 if ( ( ber_class != BER_CLASS_UNI ) || ( tag != type ) ) {
 tvb_ensure_bytes_exist ( tvb , hoffset , 2 ) ;
 cause = proto_tree_add_string_format_value ( tree , hf_ber_error , tvb , offset , len , "string_expected" , "String with tag=%d expected but class:%s(%d) %s tag:%d was unexpected" , type , val_to_str_const ( ber_class , ber_class_codes , "Unknown" ) , ber_class , pc ? ber_pc_codes_short . true_string : ber_pc_codes_short . false_string , tag ) ;
 expert_add_info ( actx -> pinfo , cause , & ei_ber_expected_string ) ;
 if ( decode_unexpected ) {
 proto_tree * unknown_tree = proto_item_add_subtree ( cause , ett_ber_unknown ) ;
 dissect_unknown_ber ( actx -> pinfo , tvb , hoffset , unknown_tree ) ;
 }
 return eoffset ;
 }
 }
 return dissect_ber_constrained_octet_string ( implicit_tag , actx , tree , tvb , hoffset , min_len , max_len , hf_id , out_tvb ) ;
 }