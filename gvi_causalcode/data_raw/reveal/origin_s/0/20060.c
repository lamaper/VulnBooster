static int dissect_h245_OLC_fw_lcn ( tvbuff_t * tvb _U_ , int offset _U_ , asn1_ctx_t * actx _U_ , proto_tree * tree _U_ , int hf_index _U_ ) {
 offset = dissect_h245_LogicalChannelNumber ( tvb , offset , actx , tree , hf_index ) ;

 h223_fw_lc_num = h245_lc_temp ;
 return offset ;
 }