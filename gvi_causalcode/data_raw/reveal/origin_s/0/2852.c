static int dissect_pvfs_handle_extent ( tvbuff_t * tvb , proto_tree * tree , int offset , packet_info * pinfo , guint32 nCount ) {
 proto_tree * extent_tree ;
 extent_tree = proto_tree_add_subtree_format ( tree , tvb , offset , 8 , ett_pvfs_extent_item , NULL , "Item %d" , nCount ) ;
 offset = dissect_pvfs_fh ( tvb , offset , pinfo , extent_tree , "first handle" , NULL ) ;
 offset = dissect_pvfs_fh ( tvb , offset , pinfo , extent_tree , "last handle" , NULL ) ;
 return offset ;
 }