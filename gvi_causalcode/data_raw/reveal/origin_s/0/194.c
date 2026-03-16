static int dissect_t38_T_primary_ifp_packet ( tvbuff_t * tvb _U_ , int offset _U_ , asn1_ctx_t * actx _U_ , proto_tree * tree _U_ , int hf_index _U_ ) {

 offset = dissect_per_open_type ( tvb , offset , actx , tree , hf_index , dissect_t38_IFPPacket ) ;

 if ( p_t38_conv ) p_t38_conv_info -> last_seqnum = ( gint32 ) seq_number ;
 return offset ;
 }