static int dissect_ber_INTEGER ( gboolean implicit_tag , tvbuff_t * tvb , int offset , asn1_ctx_t * actx , proto_tree * tree , int hf_index ) {
 offset = dissect_ber_integer ( implicit_tag , actx , tree , tvb , offset , hf_index , & actx -> external . indirect_reference ) ;
 actx -> external . indirect_ref_present = TRUE ;
 return offset ;
 }