static guint32 dissect_netb_unknown ( tvbuff_t * tvb , packet_info * pinfo , int offset , proto_tree * tree ) {
 proto_tree_add_expert ( tree , pinfo , & ei_netb_unknown_command_data , tvb , offset + NB_COMMAND + 1 , - 1 ) ;
 return 0 ;
 }