static int dissect_pvfs2_truncate_request ( tvbuff_t * tvb , proto_tree * tree , int offset , packet_info * pinfo ) {
 offset = dissect_pvfs_fh ( tvb , offset , pinfo , tree , "handle" , NULL ) ;
 offset = dissect_pvfs_fs_id ( tvb , tree , offset ) ;
 offset += 4 ;
 proto_tree_add_item ( tree , hf_pvfs_size , tvb , offset , 8 , ENC_LITTLE_ENDIAN ) ;
 offset += 8 ;
 proto_tree_add_item ( tree , hf_pvfs_truncate_request_flags , tvb , offset , 4 , ENC_LITTLE_ENDIAN ) ;
 offset += 4 ;
 return offset ;
 }