int dissect_ber_EmbeddedPDV_Type ( gboolean implicit_tag , proto_tree * tree , tvbuff_t * tvb , int offset , asn1_ctx_t * actx , gint hf_id , ber_callback func _U_ ) {
 offset = dissect_ber_tagged_type ( implicit_tag , actx , tree , tvb , offset , hf_id , BER_CLASS_UNI , BER_UNI_TAG_EMBEDDED_PDV , TRUE , dissect_ber_external_U ) ;
 return offset ;
 }