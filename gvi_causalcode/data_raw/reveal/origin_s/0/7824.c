static request_data_t * get_request ( tvbuff_t * tvb , gint offset , packet_info * pinfo , guint8 opcode , bluetooth_data_t * bluetooth_data ) {
 request_data_t * request_data ;
 wmem_tree_key_t key [ 4 ] ;
 wmem_tree_t * sub_wmemtree ;
 guint32 frame_number , curr_layer_num ;
 curr_layer_num = pinfo -> curr_layer_num ;
 key [ 0 ] . length = 1 ;
 key [ 0 ] . key = & bluetooth_data -> interface_id ;
 key [ 1 ] . length = 1 ;
 key [ 1 ] . key = & bluetooth_data -> adapter_id ;
 key [ 2 ] . length = 1 ;
 key [ 2 ] . key = & curr_layer_num ;
 key [ 3 ] . length = 0 ;
 key [ 3 ] . key = NULL ;
 frame_number = pinfo -> num ;
 sub_wmemtree = ( wmem_tree_t * ) wmem_tree_lookup32_array ( requests , key ) ;
 request_data = ( sub_wmemtree ) ? ( request_data_t * ) wmem_tree_lookup32_le ( sub_wmemtree , frame_number ) : NULL ;
 if ( request_data && request_data -> request_in_frame == pinfo -> num ) return request_data ;
 if ( request_data ) do {
 frame_number = request_data -> request_in_frame - 1 ;
 if ( request_data -> request_in_frame == pinfo -> num ) break ;
 switch ( opcode ) {
 case 0x01 : if ( tvb_captured_length_remaining ( tvb , offset ) < 1 ) return NULL ;
 opcode = tvb_get_guint8 ( tvb , 1 ) + 1 ;
 case 0x03 : case 0x05 : case 0x07 : case 0x09 : case 0x0b : case 0x0d : case 0x0f : case 0x11 : case 0x13 : case 0x17 : case 0x19 : case 0x1E : if ( request_data -> opcode == opcode - 1 ) return request_data ;
 break ;
 }
 }
 while ( 0 ) ;
 request_data = ( sub_wmemtree ) ? ( request_data_t * ) wmem_tree_lookup32_le ( sub_wmemtree , frame_number ) : NULL ;
 if ( ! request_data ) return NULL ;
 if ( request_data -> request_in_frame == pinfo -> num ) return request_data ;
 switch ( opcode ) {
 case 0x01 : if ( tvb_captured_length_remaining ( tvb , offset ) < 1 ) return NULL ;
 opcode = tvb_get_guint8 ( tvb , 1 ) + 1 ;
 case 0x03 : case 0x05 : case 0x07 : case 0x09 : case 0x0b : case 0x0d : case 0x0f : case 0x11 : case 0x13 : case 0x17 : case 0x19 : case 0x1E : if ( request_data -> opcode == opcode - 1 ) return request_data ;
 break ;
 case 0x1B : case 0x52 : case 0xD2 : return NULL ;
 case 0x02 : case 0x04 : case 0x06 : case 0x08 : case 0x0a : case 0x0c : case 0x0e : case 0x10 : case 0x12 : case 0x16 : case 0x18 : case 0x1D : default : return NULL ;
 }
 return NULL ;
 }