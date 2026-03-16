static int dissect_h245_T_object ( tvbuff_t * tvb _U_ , int offset _U_ , asn1_ctx_t * actx _U_ , proto_tree * tree _U_ , int hf_index _U_ ) {
 offset = dissect_per_object_identifier_str ( tvb , offset , actx , tree , hf_index , & nsiOID ) ;
 return offset ;
 }