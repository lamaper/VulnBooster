static void save_mtu ( packet_info * pinfo , bluetooth_data_t * bluetooth_data , guint mtu ) {
 wmem_tree_key_t key [ 4 ] ;
 guint32 frame_number ;
 mtu_data_t * mtu_data ;
 frame_number = pinfo -> num ;
 key [ 0 ] . length = 1 ;
 key [ 0 ] . key = & bluetooth_data -> interface_id ;
 key [ 1 ] . length = 1 ;
 key [ 1 ] . key = & bluetooth_data -> adapter_id ;
 key [ 2 ] . length = 1 ;
 key [ 2 ] . key = & frame_number ;
 key [ 3 ] . length = 0 ;
 key [ 3 ] . key = NULL ;
 mtu_data = wmem_new ( wmem_file_scope ( ) , mtu_data_t ) ;
 mtu_data -> mtu = mtu ;
 wmem_tree_insert32_array ( mtus , key , mtu_data ) ;
 }