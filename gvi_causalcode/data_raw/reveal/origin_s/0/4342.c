static int dissect_cip_class_s_supervisor ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , void * data _U_ ) {
 proto_item * ti ;
 proto_tree * class_tree ;
 ti = proto_tree_add_item ( tree , proto_cip_class_s_supervisor , tvb , 0 , - 1 , ENC_NA ) ;
 class_tree = proto_item_add_subtree ( ti , ett_cip_class_s_supervisor ) ;
 dissect_cip_s_supervisor_data ( class_tree , tvb , 0 , tvb_reported_length ( tvb ) , pinfo ) ;
 return tvb_reported_length ( tvb ) ;
 }