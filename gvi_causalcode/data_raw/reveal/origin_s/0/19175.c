static void dissect_mcast_byte ( proto_tree * tree , tvbuff_t * tvb , int offset , packet_info * pinfo _U_ ) {
 proto_item * mcast_item ;
 proto_tree * mcast_tree ;

 mcast_byte = tvb_get_guint8 ( tvb , offset ) ;

 mcast_tree = proto_item_add_subtree ( mcast_item , ett_cipsafety_mcast_byte ) ;
 proto_tree_add_item ( mcast_tree , hf_cipsafety_mcast_byte_consumer_num , tvb , offset , 1 , ENC_LITTLE_ENDIAN ) ;
 proto_tree_add_item ( mcast_tree , hf_cipsafety_mcast_byte_reserved1 , tvb , offset , 1 , ENC_LITTLE_ENDIAN ) ;
 proto_tree_add_item ( mcast_tree , hf_cipsafety_mcast_byte_mai , tvb , offset , 1 , ENC_LITTLE_ENDIAN ) ;
 proto_tree_add_item ( mcast_tree , hf_cipsafety_mcast_byte_reserved2 , tvb , offset , 1 , ENC_LITTLE_ENDIAN ) ;
 proto_tree_add_item ( mcast_tree , hf_cipsafety_mcast_byte_parity_even , tvb , offset , 1 , ENC_LITTLE_ENDIAN ) ;
 }