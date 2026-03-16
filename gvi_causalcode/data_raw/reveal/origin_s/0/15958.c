int dissect_ber_integer ( gboolean implicit_tag , asn1_ctx_t * actx , proto_tree * tree , tvbuff_t * tvb , int offset , gint hf_id , guint32 * value ) {
 gint64 val ;
 offset = dissect_ber_integer64 ( implicit_tag , actx , tree , tvb , offset , hf_id , & val ) ;
 if ( value ) {
 * value = ( guint32 ) val ;
 }
 return offset ;
 }