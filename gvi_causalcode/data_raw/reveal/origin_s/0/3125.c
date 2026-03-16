static int dissect_h225_DestinationInfo_item ( tvbuff_t * tvb _U_ , int offset _U_ , asn1_ctx_t * actx _U_ , proto_tree * tree _U_ , int hf_index _U_ ) {

 h225_pi = ( h225_packet_info * ) p_get_proto_data ( wmem_packet_scope ( ) , actx -> pinfo , proto_h225 , 0 ) ;
 if ( h225_pi != NULL ) {
 h225_pi -> is_destinationInfo = TRUE ;
 }
 offset = dissect_h225_AliasAddress ( tvb , offset , actx , tree , hf_index ) ;
 return offset ;
 }