static int dissect_pvfs2_write_completion_response ( tvbuff_t * tvb , proto_tree * tree , int offset ) {
 offset = dissect_pvfs_uint64 ( tvb , tree , offset , hf_pvfs_total_completed , NULL ) ;
 return offset ;
 }