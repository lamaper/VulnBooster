static int dissect_pvfs2_readdir_response ( tvbuff_t * tvb , proto_tree * tree , int offset , packet_info * pinfo ) {
 guint32 dirent_count = 0 ;
 guint32 nCount = 0 ;
 proto_tree_add_item ( tree , hf_pvfs_ds_position , tvb , offset , 4 , ENC_LITTLE_ENDIAN ) ;
 offset += 4 ;
 offset += 4 ;
 proto_tree_add_item ( tree , hf_pvfs_directory_version , tvb , offset , 8 , ENC_LITTLE_ENDIAN ) ;
 offset += 8 ;
 offset += 4 ;
 dirent_count = tvb_get_letohl ( tvb , offset ) ;
 proto_tree_add_item ( tree , hf_pvfs_dirent_count , tvb , offset , 4 , ENC_LITTLE_ENDIAN ) ;
 offset += 4 ;
 for ( nCount = 0 ;
 nCount < dirent_count ;
 nCount ++ ) {
 offset = dissect_pvfs_string ( tvb , tree , hf_pvfs_path , offset , NULL ) ;
 offset = dissect_pvfs_fh ( tvb , offset , pinfo , tree , "handle" , NULL ) ;
 }
 return offset ;
 }