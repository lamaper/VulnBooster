int dissect_ber_constrained_integer ( gboolean implicit_tag , asn1_ctx_t * actx , proto_tree * tree , tvbuff_t * tvb , int offset , gint32 min_len , gint32 max_len , gint hf_id , guint32 * value ) {
 gint64 val ;
 offset = dissect_ber_integer64 ( implicit_tag , actx , tree , tvb , offset , hf_id , & val ) ;
 if ( value ) {
 * value = ( guint32 ) val ;
 }
 ber_check_value ( ( guint32 ) val , min_len , max_len , actx , actx -> created_item ) ;
 return offset ;
 }