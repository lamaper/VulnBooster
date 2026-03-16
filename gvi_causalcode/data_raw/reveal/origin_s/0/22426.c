static int dissect_btgatt_microbit_magnetometer_data ( tvbuff_t * tvb , packet_info * pinfo _U_ , proto_tree * tree , void * data ) {
 btatt_data_t * att_data = ( btatt_data_t * ) data ;
 proto_item * sub_item ;
 proto_tree * sub_tree ;
 gdouble x_axis , y_axis , z_axis ;
 gint offset = 0 ;
 if ( bluetooth_gatt_has_no_parameter ( att_data -> opcode ) ) return - 1 ;
 x_axis = ( gdouble ) ( gint ) tvb_get_gint16 ( tvb , offset , ENC_LITTLE_ENDIAN ) / 1000.0 ;
 y_axis = ( gdouble ) ( gint ) tvb_get_gint16 ( tvb , offset + 2 , ENC_LITTLE_ENDIAN ) / 1000.0 ;
 z_axis = ( gdouble ) ( gint ) tvb_get_gint16 ( tvb , offset + 4 , ENC_LITTLE_ENDIAN ) / 1000.0 ;
 sub_item = proto_tree_add_item ( tree , hf_gatt_microbit_magnetometer_data , tvb , 0 , tvb_captured_length ( tvb ) , ENC_NA ) ;
 sub_tree = proto_item_add_subtree ( sub_item , ett_btgatt_microbit_magnetometer ) ;
 proto_item_append_text ( sub_item , " (X: %f, Y: %f, Z: %f)" , x_axis , y_axis , z_axis ) ;
 proto_tree_add_double ( sub_tree , hf_gatt_microbit_magnetometer_x , tvb , offset , 2 , x_axis ) ;
 offset += 2 ;
 proto_tree_add_double ( sub_tree , hf_gatt_microbit_magnetometer_y , tvb , offset , 2 , y_axis ) ;
 offset += 2 ;
 proto_tree_add_double ( sub_tree , hf_gatt_microbit_magnetometer_z , tvb , offset , 2 , z_axis ) ;
 offset += 2 ;
 return offset ;
 }