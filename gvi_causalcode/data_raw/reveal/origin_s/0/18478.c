int dissect_ber_constrained_integer64 ( gboolean implicit_tag , asn1_ctx_t * actx , proto_tree * tree , tvbuff_t * tvb , int offset , gint64 min_len , gint64 max_len , gint hf_id , gint64 * value ) {
 gint64 val ;
 offset = dissect_ber_integer64 ( implicit_tag , actx , tree , tvb , offset , hf_id , & val ) ;
 if ( value ) {
 * value = val ;
 }
 ber_check_value64 ( val , min_len , max_len , actx , actx -> created_item ) ;
 return offset ;
 }