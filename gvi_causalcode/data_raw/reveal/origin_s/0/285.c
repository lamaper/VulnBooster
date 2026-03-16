int dissect_ber_bitstring ( gboolean implicit_tag , asn1_ctx_t * actx , proto_tree * parent_tree , tvbuff_t * tvb , int offset , const asn_namedbit * named_bits , gint hf_id , gint ett_id , tvbuff_t * * out_tvb ) {
 return dissect_ber_constrained_bitstring ( implicit_tag , actx , parent_tree , tvb , offset , - 1 , - 1 , named_bits , hf_id , ett_id , out_tvb ) ;
 }