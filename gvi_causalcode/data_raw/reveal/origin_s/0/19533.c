static int dissect_ber_T_octet_aligned ( gboolean implicit_tag _U_ , tvbuff_t * tvb _U_ , int offset _U_ , asn1_ctx_t * actx _U_ , proto_tree * tree _U_ , int hf_index _U_ ) {
 if ( actx -> external . u . ber . ber_callback ) {
 offset = actx -> external . u . ber . ber_callback ( FALSE , tvb , offset , actx , tree , hf_index ) ;
 }
 else if ( actx -> external . direct_ref_present && dissector_get_string_handle ( ber_oid_dissector_table , actx -> external . direct_reference ) ) {
 offset = call_ber_oid_callback ( actx -> external . direct_reference , tvb , offset , actx -> pinfo , tree , NULL ) ;
 }
 else {
 offset = dissect_ber_octet_string ( implicit_tag , actx , tree , tvb , offset , hf_index , & actx -> external . octet_aligned ) ;
 }
 return offset ;
 }