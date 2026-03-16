static int dissect_btgatt_nordic_dfu_control_point ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , void * data ) {
 gint offset = 0 ;
 guint8 opcode ;
 guint8 request_opcode ;
 guint8 status ;
 btatt_data_t * att_data = ( btatt_data_t * ) data ;
 if ( bluetooth_gatt_has_no_parameter ( att_data -> opcode ) ) return - 1 ;
 proto_tree_add_item ( tree , hf_gatt_nordic_dfu_control_point_opcode , tvb , offset , 1 , ENC_NA ) ;
 opcode = tvb_get_guint8 ( tvb , offset ) ;
 offset += 1 ;
 switch ( opcode ) {
 case 0x01 : proto_tree_add_item ( tree , hf_gatt_nordic_dfu_control_point_image_type , tvb , offset , 1 , ENC_NA ) ;
 offset += 1 ;
 break ;
 case 0x02 : if ( tvb_reported_length_remaining ( tvb , offset ) > 0 ) {
 proto_tree_add_item ( tree , hf_gatt_nordic_dfu_control_point_init_packet , tvb , offset , 1 , ENC_NA ) ;
 offset += 1 ;
 }
 break ;
 case 0x03 : case 0x04 : case 0x05 : case 0x06 : case 0x07 : break ;
 case 0x08 : proto_tree_add_item ( tree , hf_gatt_nordic_dfu_control_point_number_of_packets , tvb , offset , 2 , ENC_LITTLE_ENDIAN ) ;
 offset += 2 ;
 break ;
 case 0x10 : proto_tree_add_item ( tree , hf_gatt_nordic_dfu_control_point_request_opcode , tvb , offset , 1 , ENC_NA ) ;
 request_opcode = tvb_get_guint8 ( tvb , offset ) ;
 offset += 1 ;
 proto_tree_add_item ( tree , hf_gatt_nordic_dfu_control_point_response_value , tvb , offset , 1 , ENC_NA ) ;
 status = tvb_get_guint8 ( tvb , offset ) ;
 offset += 1 ;
 if ( request_opcode == 0x07 && status == 0x01 ) {
 proto_tree_add_item ( tree , hf_gatt_nordic_dfu_control_point_number_of_bytes , tvb , offset , 4 , ENC_LITTLE_ENDIAN ) ;
 offset += 4 ;
 }
 break ;
 case 0x11 : proto_tree_add_item ( tree , hf_gatt_nordic_dfu_control_point_number_of_bytes , tvb , offset , 4 , ENC_LITTLE_ENDIAN ) ;
 offset += 4 ;
 break ;
 }
 if ( tvb_captured_length_remaining ( tvb , offset ) > 0 ) {
 proto_tree_add_expert ( tree , pinfo , & ei_btatt_unexpected_data , tvb , offset , - 1 ) ;
 offset = tvb_captured_length ( tvb ) ;
 }
 return offset ;
 }