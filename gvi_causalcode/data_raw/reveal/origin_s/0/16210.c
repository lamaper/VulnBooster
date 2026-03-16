static int dissect_nlm4_unlock ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , void * data ) {
 return dissect_nlm_unlock ( tvb , 0 , pinfo , tree , 4 , ( rpc_call_info_value * ) data ) ;
 }