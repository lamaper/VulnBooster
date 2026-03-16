static guint get_mtu ( packet_info * pinfo , bluetooth_data_t * bluetooth_data ) {
 wmem_tree_key_t key [ 3 ] ;
 guint32 frame_number ;
 mtu_data_t * mtu_data ;
 wmem_tree_t * sub_wmemtree ;
 guint mtu = 23 ;
 frame_number = pinfo -> num ;
 key [ 0 ] . length = 1 ;
 key [ 0 ] . key = & bluetooth_data -> interface_id ;
 key [ 1 ] . length = 1 ;
 key [ 1 ] . key = & bluetooth_data -> adapter_id ;
 key [ 2 ] . length = 0 ;
 key [ 2 ] . key = NULL ;
 sub_wmemtree = ( wmem_tree_t * ) wmem_tree_lookup32_array ( mtus , key ) ;
 mtu_data = ( sub_wmemtree ) ? ( mtu_data_t * ) wmem_tree_lookup32_le ( sub_wmemtree , frame_number ) : NULL ;
 if ( mtu_data ) mtu = mtu_data -> mtu ;
 return mtu ;
 }