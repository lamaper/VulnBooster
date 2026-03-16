static int dissect_h245_T_h223_lc_segmentableFlag ( tvbuff_t * tvb _U_ , int offset _U_ , asn1_ctx_t * actx _U_ , proto_tree * tree _U_ , int hf_index _U_ ) {

 offset = dissect_per_boolean ( tvb , offset , actx , tree , hf_index , & value ) ;
 if ( h223_lc_params_temp ) h223_lc_params_temp -> segmentable = value ;
 return offset ;
 }