static int dissect_btgatt_microbit_pin_io_config ( tvbuff_t * tvb , packet_info * pinfo _U_ , proto_tree * tree , void * data ) {
 btatt_data_t * att_data = ( btatt_data_t * ) data ;
 proto_item * sub_item ;
 proto_tree * sub_tree ;
 if ( bluetooth_gatt_has_no_parameter ( att_data -> opcode ) ) return - 1 ;
 sub_item = proto_tree_add_item ( tree , hf_gatt_microbit_pin_io_config , tvb , 0 , 3 , ENC_LITTLE_ENDIAN ) ;
 sub_tree = proto_item_add_subtree ( sub_item , ett_btgatt_microbit_pin_io_config ) ;
 proto_tree_add_bitmask_list ( sub_tree , tvb , 0 , 3 , hfx_btgatt_microbit_io_pins , ENC_LITTLE_ENDIAN ) ;
 return tvb_captured_length ( tvb ) ;
 }