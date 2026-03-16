int dissect_ber_boolean ( gboolean implicit_tag , asn1_ctx_t * actx , proto_tree * tree , tvbuff_t * tvb , int offset , gint hf_id , gboolean * value ) {
 gint8 ber_class ;
 gboolean pc ;
 gint32 tag ;
 guint32 len ;
 guint8 val ;
 header_field_info * hfi ;
 if ( ! implicit_tag ) {
 offset = dissect_ber_identifier ( actx -> pinfo , tree , tvb , offset , & ber_class , & pc , & tag ) ;
 offset = dissect_ber_length ( actx -> pinfo , tree , tvb , offset , & len , NULL ) ;
 }
 else {
 }
 val = tvb_get_guint8 ( tvb , offset ) ;
 offset += 1 ;
 actx -> created_item = NULL ;
 if ( hf_id >= 0 ) {
 hfi = proto_registrar_get_nth ( hf_id ) ;
 if ( hfi -> type == FT_BOOLEAN ) actx -> created_item = proto_tree_add_boolean ( tree , hf_id , tvb , offset - 1 , 1 , val ) ;
 else actx -> created_item = proto_tree_add_uint ( tree , hf_id , tvb , offset - 1 , 1 , val ? 1 : 0 ) ;
 }
 if ( value ) {
 * value = ( val ? TRUE : FALSE ) ;
 }
 return offset ;
 }