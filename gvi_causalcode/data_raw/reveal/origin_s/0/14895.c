static int dissect_h245_T_logicalChannelNum ( tvbuff_t * tvb _U_ , int offset _U_ , asn1_ctx_t * actx _U_ , proto_tree * tree _U_ , int hf_index _U_ ) {

 offset = dissect_per_constrained_integer ( tvb , offset , actx , tree , hf_index , 0U , 65535U , & value , FALSE ) ;
 h223_me -> sublist = NULL ;
 h223_me -> vc = value & 0xffff ;
 return offset ;
 }