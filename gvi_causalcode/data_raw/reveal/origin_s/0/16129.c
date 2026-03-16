static void save_handle ( packet_info * pinfo , bluetooth_uuid_t uuid , guint32 handle , enum attribute_type attribute_type , bluetooth_data_t * bluetooth_data ) {
 if ( ! handle && uuid . size != 2 && uuid . size != 16 ) return ;
 if ( have_tap_listener ( btatt_tap_handles ) ) {
 tap_handles_t * tap_handles ;
 tap_handles = wmem_new ( wmem_packet_scope ( ) , tap_handles_t ) ;
 tap_handles -> handle = handle ;
 tap_handles -> uuid = uuid ;
 tap_queue_packet ( btatt_tap_handles , pinfo , tap_handles ) ;
 }
 if ( ! pinfo -> fd -> flags . visited && bluetooth_data ) {
 wmem_tree_key_t key [ 5 ] ;
 guint32 frame_number ;
 handle_data_t * handle_data ;
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
 handle_data = wmem_new ( wmem_file_scope ( ) , handle_data_t ) ;
 handle_data -> uuid = uuid ;
 handle_data -> type = attribute_type ;
 wmem_tree_insert32_array ( handle_to_uuid , key , handle_data ) ;
 }
 }