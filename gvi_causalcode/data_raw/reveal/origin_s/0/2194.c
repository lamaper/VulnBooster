static int dissect_pvfs_time ( tvbuff_t * tvb , proto_tree * tree , int offset , int hf_time , int hf_time_sec , int hf_time_nsec ) {
 guint32 seconds ;
 guint32 nseconds ;
 nstime_t ts ;
 proto_item * time_item ;
 proto_tree * time_tree ;
 ts . secs = seconds = tvb_get_letohl ( tvb , offset ) ;
 ts . nsecs = nseconds = tvb_get_letohl ( tvb , offset + 4 ) ;
 time_item = proto_tree_add_time ( tree , hf_time , tvb , offset , 8 , & ts ) ;
 time_tree = proto_item_add_subtree ( time_item , ett_pvfs_time ) ;
 proto_tree_add_uint ( time_tree , hf_time_sec , tvb , offset , 4 , seconds ) ;
 proto_tree_add_uint ( time_tree , hf_time_nsec , tvb , offset + 4 , 4 , nseconds ) ;
 offset += 8 ;
 return offset ;
 }