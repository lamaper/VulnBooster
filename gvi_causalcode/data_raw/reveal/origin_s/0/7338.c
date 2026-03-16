static int dissect_diameter_vendor_id ( tvbuff_t * tvb , packet_info * pinfo _U_ , proto_tree * tree , void * data _U_ ) {
 int offset = 0 ;
 proto_tree_add_item ( tree , hf_diameter_vendor_id , tvb , 0 , 4 , ENC_BIG_ENDIAN ) ;
 offset ++ ;
 return offset ;
 }