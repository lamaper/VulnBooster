static int dissect_ber_OBJECT_IDENTIFIER ( gboolean implicit_tag , tvbuff_t * tvb , int offset , asn1_ctx_t * actx , proto_tree * tree , int hf_index ) {
 offset = dissect_ber_object_identifier_str ( implicit_tag , actx , tree , tvb , offset , hf_index , & actx -> external . direct_reference ) ;
 actx -> external . direct_ref_present = TRUE ;
 return offset ;
 }