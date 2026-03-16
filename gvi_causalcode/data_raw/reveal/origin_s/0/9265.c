static int dissect_h225_T_h245Ip ( tvbuff_t * tvb _U_ , int offset _U_ , asn1_ctx_t * actx _U_ , proto_tree * tree _U_ , int hf_index _U_ ) {

 ipv4_address = 0 ;
 offset = dissect_per_octet_string ( tvb , offset , actx , tree , hf_index , 4 , 4 , FALSE , & value_tvb ) ;
 if ( value_tvb ) ipv4_address = tvb_get_ipv4 ( value_tvb , 0 ) ;
 return offset ;
 }