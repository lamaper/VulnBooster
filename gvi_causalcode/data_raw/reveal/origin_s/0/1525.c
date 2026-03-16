static int dissect_btgatt_microbit_temperature_value ( tvbuff_t * tvb , packet_info * pinfo _U_ , proto_tree * tree , void * data ) {
 btatt_data_t * att_data = ( btatt_data_t * ) data ;
 gint offset = 0 ;
 if ( bluetooth_gatt_has_no_parameter ( att_data -> opcode ) ) return - 1 ;
 proto_tree_add_item ( tree , hf_gatt_microbit_temperature_value , tvb , offset , 1 , ENC_NA ) ;
 offset += 1 ;
 return offset ;
 }