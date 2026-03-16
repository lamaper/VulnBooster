static int dissect_h245_OLC_rev_h223_params ( tvbuff_t * tvb _U_ , int offset _U_ , asn1_ctx_t * actx _U_ , proto_tree * tree _U_ , int hf_index _U_ ) {

 h223_rev_lc_params -> al_type = al_nonStandard ;
 h223_rev_lc_params -> al_params = NULL ;
 h223_rev_lc_params -> segmentable = 0 ;
 h223_rev_lc_params -> subdissector = NULL ;
 h223_lc_params_temp = h223_rev_lc_params ;
 offset = dissect_h245_H223LogicalChannelParameters ( tvb , offset , actx , tree , hf_index ) ;
 return offset ;
 }