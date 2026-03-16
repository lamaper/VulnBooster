static void dissect_mode_byte ( proto_tree * tree , tvbuff_t * tvb , int offset , packet_info * pinfo ) {
 proto_item * mode_item , * run_idle_item , * tbd_item , * tbd2_item ;
 proto_tree * mode_tree ;
 guint8 mode_byte ;
 mode_byte = tvb_get_guint8 ( tvb , offset ) ;
 mode_item = proto_tree_add_item ( tree , hf_cipsafety_mode_byte , tvb , offset , 1 , ENC_LITTLE_ENDIAN ) ;
 mode_tree = proto_item_add_subtree ( mode_item , ett_cipsafety_mode_byte ) ;
 proto_tree_add_item ( mode_tree , hf_cipsafety_mode_byte_ping_count , tvb , offset , 1 , ENC_LITTLE_ENDIAN ) ;
 proto_tree_add_item ( mode_tree , hf_cipsafety_mode_byte_not_tbd , tvb , offset , 1 , ENC_LITTLE_ENDIAN ) ;
 proto_tree_add_item ( mode_tree , hf_cipsafety_mode_byte_tbd_2_copy , tvb , offset , 1 , ENC_LITTLE_ENDIAN ) ;
 proto_tree_add_item ( mode_tree , hf_cipsafety_mode_byte_not_run_idle , tvb , offset , 1 , ENC_LITTLE_ENDIAN ) ;
 tbd_item = proto_tree_add_item ( mode_tree , hf_cipsafety_mode_byte_tbd , tvb , offset , 1 , ENC_LITTLE_ENDIAN ) ;
 tbd2_item = proto_tree_add_item ( mode_tree , hf_cipsafety_mode_byte_tbd_2_bit , tvb , offset , 1 , ENC_LITTLE_ENDIAN ) ;
 run_idle_item = proto_tree_add_item ( mode_tree , hf_cipsafety_mode_byte_run_idle , tvb , offset , 1 , ENC_LITTLE_ENDIAN ) ;
 if ( ( ( ( mode_byte & 0x20 ) >> 5 ) & 0x01 ) == ( ( ( mode_byte & 0x04 ) >> 2 ) & 0x01 ) ) expert_add_info ( pinfo , tbd_item , & ei_cipsafety_tbd2_not_complemented ) ;
 if ( ( ( ( mode_byte & 0x40 ) >> 6 ) & 0x01 ) != ( ( ( mode_byte & 0x08 ) >> 3 ) & 0x01 ) ) expert_add_info ( pinfo , tbd2_item , & ei_cipsafety_tbd_not_copied ) ;
 if ( ( ( ( mode_byte & 0x80 ) >> 7 ) & 0x01 ) == ( ( ( mode_byte & 0x10 ) >> 4 ) & 0x01 ) ) expert_add_info ( pinfo , run_idle_item , & ei_cipsafety_run_idle_not_complemented ) ;
 }