static int dissect_h245_T_mode_rfc2733diffport ( tvbuff_t * tvb _U_ , int offset _U_ , asn1_ctx_t * actx _U_ , proto_tree * tree _U_ , int hf_index _U_ ) {
 offset = dissect_per_sequence ( tvb , offset , actx , tree , hf_index , ett_h245_T_mode_rfc2733diffport , T_mode_rfc2733diffport_sequence ) ;
 return offset ;
 }