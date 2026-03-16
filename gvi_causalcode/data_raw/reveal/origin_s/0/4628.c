static int dissect_h245_T_rtpPayloadType ( tvbuff_t * tvb _U_ , int offset _U_ , asn1_ctx_t * actx _U_ , proto_tree * tree _U_ , int hf_index _U_ ) {

 offset = dissect_per_constrained_integer ( tvb , offset , actx , tree , hf_index , 0U , 127U , & pt , FALSE ) ;
 if ( ( rfc_number == 2198 ) && upcoming_channel ) {
 upcoming_channel -> rfc2198 = pt ;
 }
 return offset ;
 }