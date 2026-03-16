static int dissect_h225_T_empty_flg ( tvbuff_t * tvb _U_ , int offset _U_ , asn1_ctx_t * actx _U_ , proto_tree * tree _U_ , int hf_index _U_ ) {

 offset = dissect_per_null ( tvb , offset , actx , tree , hf_index ) ;

 if ( h225_pi != NULL ) {
 h225_pi -> cs_type = H225_EMPTY ;
 }
 return offset ;
 }