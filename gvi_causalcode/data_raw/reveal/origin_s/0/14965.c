static void save_value_fragment ( packet_info * pinfo , tvbuff_t * tvb , gint offset , guint32 handle , guint data_offset , bluetooth_data_t * bluetooth_data ) {
 wmem_tree_key_t key [ 5 ] ;
 guint32 frame_number ;
 fragment_data_t * fragment_data ;
 frame_number = pinfo -> num ;
 key [ 0 ] . length = 1 ;
 key [ 0 ] . key = & bluetooth_data -> interface_id ;
 key [ 1 ] . length = 1 ;
 key [ 1 ] . key = & bluetooth_data -> adapter_id ;
 key [ 2 ] . length = 1 ;
 key [ 2 ] . key = & handle ;
 key [ 3 ] . length = 1 ;
 key [ 3 ] . key = & frame_number ;
 key [ 4 ] . length = 0 ;
 key [ 4 ] . key = NULL ;
 fragment_data = wmem_new ( wmem_file_scope ( ) , fragment_data_t ) ;
 fragment_data -> length = tvb_captured_length_remaining ( tvb , offset ) ;
 fragment_data -> offset = data_offset ;
 fragment_data -> data_in_frame = frame_number ;
 fragment_data -> data = ( guint8 * ) tvb_memdup ( wmem_file_scope ( ) , tvb , offset , fragment_data -> length ) ;
 wmem_tree_insert32_array ( fragments , key , fragment_data ) ;
 }