static int dissect_ber_T_arbitrary ( gboolean implicit_tag _U_ , tvbuff_t * tvb _U_ , int offset _U_ , asn1_ctx_t * actx _U_ , proto_tree * tree _U_ , int hf_index _U_ ) {
 if ( actx -> external . u . ber . ber_callback ) {
 offset = actx -> external . u . ber . ber_callback ( FALSE , tvb , offset , actx , tree , hf_index ) ;
 }
 else {
 offset = dissect_ber_bitstring ( implicit_tag , actx , tree , tvb , offset , NULL , hf_index , - 1 , & actx -> external . arbitrary ) ;
 }
 return offset ;
 }