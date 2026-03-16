int dissect_unknown_ber ( packet_info * pinfo , tvbuff_t * tvb , int offset , proto_tree * tree ) {
 return try_dissect_unknown_ber ( pinfo , tvb , offset , tree , 1 ) ;
 }