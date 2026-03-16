static int dissect_cipsafety ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , void * data _U_ ) {
 proto_item * ti ;
 proto_tree * safety_tree ;
 ti = proto_tree_add_item ( tree , proto_cipsafety , tvb , 0 , - 1 , ENC_NA ) ;
 safety_tree = proto_item_add_subtree ( ti , ett_cip_safety ) ;
 dissect_cip_safety_data ( safety_tree , ti , tvb , tvb_reported_length ( tvb ) , pinfo ) ;
 return tvb_captured_length ( tvb ) ;
 }