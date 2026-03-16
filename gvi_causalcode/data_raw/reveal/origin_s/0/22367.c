static int dissect_pvfs_handle_extent_array ( tvbuff_t * tvb , proto_tree * tree , int offset , packet_info * pinfo ) {
 guint32 extent_count ;
 guint32 nCount ;
 proto_tree * extent_array_tree ;
 extent_count = tvb_get_letohl ( tvb , offset ) ;
 extent_array_tree = proto_tree_add_subtree_format ( tree , tvb , offset , 4 , ett_pvfs_extent_array_tree , NULL , "Handle Extent Array (count = %d)" , extent_count ) ;
 offset += 4 ;
 if ( extent_count > 0 ) {
 for ( nCount = 0 ;
 nCount < extent_count ;
 nCount ++ ) offset = dissect_pvfs_handle_extent ( tvb , extent_array_tree , offset , pinfo , nCount ) ;
 }
 return offset ;
 }