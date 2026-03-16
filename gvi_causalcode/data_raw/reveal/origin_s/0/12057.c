static int dissect_nlm3_shareres ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , void * data _U_ ) {
 return dissect_nlm_shareres ( tvb , 0 , pinfo , tree , 3 ) ;
 }