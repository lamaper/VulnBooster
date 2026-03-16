static int dissect_h225_T_h4501SupplementaryService_item ( tvbuff_t * tvb _U_ , int offset _U_ , asn1_ctx_t * actx _U_ , proto_tree * tree _U_ , int hf_index _U_ ) {

 offset = dissect_per_octet_string ( tvb , offset , actx , tree , hf_index , NO_BOUND , NO_BOUND , FALSE , & h4501_tvb ) ;
 if ( h4501_tvb && tvb_reported_length ( h4501_tvb ) ) {
 call_dissector ( h4501_handle , h4501_tvb , actx -> pinfo , tree ) ;
 }
 return offset ;
 }