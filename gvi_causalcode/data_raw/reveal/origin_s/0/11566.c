static int dissect_h245_Ipv4_network ( tvbuff_t * tvb _U_ , int offset _U_ , asn1_ctx_t * actx _U_ , proto_tree * tree _U_ , int hf_index _U_ ) {

 offset = dissect_per_octet_string ( tvb , offset , actx , tree , hf_index , 4 , 4 , FALSE , & value_tvb ) ;
 if ( upcoming_channel && upcoming_channel -> upcoming_addr ) {
 tvb_memcpy ( value_tvb , upcoming_channel -> upcoming_addr -> addr_buf , 0 , 4 ) ;
 SET_ADDRESS ( & upcoming_channel -> upcoming_addr -> addr , AT_IPv4 , 4 , upcoming_channel -> upcoming_addr -> addr_buf ) ;
 }
 return offset ;
 }