static bluetooth_uuid_t get_uuid_from_handle ( packet_info * pinfo , guint32 handle , bluetooth_data_t * bluetooth_data ) {
 wmem_tree_key_t key [ 4 ] ;
 guint32 frame_number ;
 handle_data_t * handle_data ;
 wmem_tree_t * sub_wmemtree ;
 bluetooth_uuid_t uuid ;
 memset ( & uuid , 0 , sizeof uuid ) ;
 frame_number = pinfo -> num ;
 key [ 0 ] . length = 1 ;
 key [ 0 ] . key = & bluetooth_data -> interface_id ;
 key [ 1 ] . length = 1 ;
 key [ 1 ] . key = & bluetooth_data -> adapter_id ;
 key [ 2 ] . length = 1 ;
 key [ 2 ] . key = & handle ;
 key [ 3 ] . length = 0 ;
 key [ 3 ] . key = NULL ;
 sub_wmemtree = ( wmem_tree_t * ) wmem_tree_lookup32_array ( handle_to_uuid , key ) ;
 handle_data = ( sub_wmemtree ) ? ( handle_data_t * ) wmem_tree_lookup32_le ( sub_wmemtree , frame_number ) : NULL ;
 if ( handle_data ) uuid = handle_data -> uuid ;
 return uuid ;
 }