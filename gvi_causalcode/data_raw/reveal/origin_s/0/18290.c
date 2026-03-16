static int dissect_pvfs2_chdirent_request ( tvbuff_t * tvb , proto_tree * tree , int offset , packet_info * pinfo ) {
 offset = dissect_pvfs_string ( tvb , tree , hf_pvfs_path , offset , NULL ) ;
 offset = dissect_pvfs_fh ( tvb , offset , pinfo , tree , "new directory handle" , NULL ) ;
 offset = dissect_pvfs_fh ( tvb , offset , pinfo , tree , "parent handle" , NULL ) ;
 offset = dissect_pvfs_fs_id ( tvb , tree , offset ) ;
 offset = dissect_pvfs_time ( tvb , tree , offset , hf_pvfs_parent_atime , hf_pvfs_parent_atime_sec , hf_pvfs_parent_atime_nsec ) ;
 offset = dissect_pvfs_time ( tvb , tree , offset , hf_pvfs_parent_mtime , hf_pvfs_parent_mtime_sec , hf_pvfs_parent_mtime_nsec ) ;
 offset = dissect_pvfs_time ( tvb , tree , offset , hf_pvfs_parent_ctime , hf_pvfs_parent_ctime_sec , hf_pvfs_parent_ctime_nsec ) ;
 return offset ;
 }