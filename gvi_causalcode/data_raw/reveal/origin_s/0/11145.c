static int dissect_nlm3_share ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , void * data _U_ ) {
 return dissect_nlm_share ( tvb , 0 , pinfo , tree , 3 , ( rpc_call_info_value * ) data ) ;
 }