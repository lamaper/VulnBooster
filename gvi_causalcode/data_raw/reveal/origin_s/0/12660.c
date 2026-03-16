int dissect_ber_external_type ( gboolean implicit_tag , proto_tree * tree , tvbuff_t * tvb , int offset , asn1_ctx_t * actx , gint hf_id , ber_callback func ) {
 actx -> external . u . ber . ber_callback = func ;
 offset = dissect_ber_tagged_type ( implicit_tag , actx , tree , tvb , offset , hf_id , BER_CLASS_UNI , BER_UNI_TAG_EXTERNAL , TRUE , dissect_ber_external_U ) ;
 asn1_ctx_clean_external ( actx ) ;
 return offset ;
 }