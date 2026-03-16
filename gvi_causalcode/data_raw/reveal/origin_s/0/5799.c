static int dissect_h225_T_guid ( tvbuff_t * tvb _U_ , int offset _U_ , asn1_ctx_t * actx _U_ , proto_tree * tree _U_ , int hf_index _U_ ) {

 actx -> value_ptr = & guid_tvb ;
 offset = dissect_h225_GloballyUniqueID ( tvb , offset , actx , tree , hf_index ) ;
 if ( guid_tvb ) tvb_get_ntohguid ( guid_tvb , 0 , call_id_guid = wmem_new ( wmem_packet_scope ( ) , e_guid_t ) ) ;
 actx -> value_ptr = NULL ;
 return offset ;
 }