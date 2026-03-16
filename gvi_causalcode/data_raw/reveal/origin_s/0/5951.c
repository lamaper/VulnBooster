static int dissect_btgatt_microbit_pin_data ( tvbuff_t * tvb , packet_info * pinfo _U_ , proto_tree * tree , void * data ) {
 btatt_data_t * att_data = ( btatt_data_t * ) data ;
 proto_item * sub_item ;
 proto_tree * sub_tree ;
 gint offset = 0 ;
 gint num_pins ;
 guint32 number , value ;
 if ( bluetooth_gatt_has_no_parameter ( att_data -> opcode ) ) return - 1 ;
 num_pins = tvb_captured_length ( tvb ) / 2 ;
 for ( gint i = 0 ;
 i < num_pins ;
 i ++ ) {
 sub_item = proto_tree_add_item ( tree , hf_gatt_microbit_pin_data , tvb , offset , 2 , ENC_NA ) ;
 sub_tree = proto_item_add_subtree ( sub_item , ett_btgatt_microbit_pin_data ) ;
 proto_tree_add_item_ret_uint ( sub_tree , hf_gatt_microbit_pin_number , tvb , offset , 1 , ENC_NA , & number ) ;
 offset ++ ;
 value = tvb_get_guint8 ( tvb , offset ) * 4 ;
 proto_tree_add_uint ( sub_tree , hf_gatt_microbit_pin_value , tvb , offset , 1 , value ) ;
 offset ++ ;
 proto_item_set_text ( sub_item , "Pin %u: %u" , number , value ) ;
 }
 return offset ;
 }