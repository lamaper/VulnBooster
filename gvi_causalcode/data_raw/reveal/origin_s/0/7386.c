static int dissect_pvfs2_mgmt_remove_dirent_request ( tvbuff_t * tvb , proto_tree * tree , int offset , packet_info * pinfo ) {
 offset = dissect_pvfs_fh ( tvb , offset , pinfo , tree , "handle" , NULL ) ;
 offset = dissect_pvfs_fs_id ( tvb , tree , offset ) ;
 offset += 4 ;
 offset = dissect_pvfs_string ( tvb , tree , hf_pvfs_path , offset , NULL ) ;
 return offset ;
 }