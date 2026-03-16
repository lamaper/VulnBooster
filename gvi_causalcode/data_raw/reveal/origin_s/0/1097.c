static int dissect_pvfs_object_attr ( tvbuff_t * tvb , proto_tree * tree , int offset , packet_info * pinfo ) {
 gint32 ds_type = 0 ;
 guint32 attrmask = 0 ;
 proto_tree * attr_tree ;
 attr_tree = proto_tree_add_subtree ( tree , tvb , offset , - 1 , ett_pvfs_attr_tree , NULL , "Attributes" ) ;
 proto_tree_add_item ( attr_tree , hf_pvfs_uid , tvb , offset , 4 , ENC_LITTLE_ENDIAN ) ;
 offset += 4 ;
 proto_tree_add_item ( attr_tree , hf_pvfs_gid , tvb , offset , 4 , ENC_LITTLE_ENDIAN ) ;
 offset += 4 ;
 proto_tree_add_item ( attr_tree , hf_pvfs_permissions , tvb , offset , 4 , ENC_LITTLE_ENDIAN ) ;
 offset += 4 ;
 offset += 4 ;
 offset = dissect_pvfs_time ( tvb , attr_tree , offset , hf_pvfs_atime , hf_pvfs_atime_sec , hf_pvfs_atime_nsec ) ;
 offset = dissect_pvfs_time ( tvb , attr_tree , offset , hf_pvfs_mtime , hf_pvfs_mtime_sec , hf_pvfs_mtime_nsec ) ;
 offset = dissect_pvfs_time ( tvb , attr_tree , offset , hf_pvfs_ctime , hf_pvfs_ctime_sec , hf_pvfs_ctime_nsec ) ;
 offset = dissect_pvfs2_attrmask ( tvb , attr_tree , offset , & attrmask ) ;
 offset = dissect_pvfs2_ds_type ( tvb , attr_tree , offset , & ds_type ) ;
 if ( attrmask & PVFS_ATTR_META_DIST ) {
 offset = dissect_pvfs_distribution ( tvb , attr_tree , offset ) ;
 offset = dissect_pvfs_meta_attr_dfiles ( tvb , attr_tree , offset , pinfo ) ;
 }
 else {
 if ( attrmask & PVFS_ATTR_META_DFILES ) {
 offset = dissect_pvfs_meta_attr_dfiles ( tvb , attr_tree , offset , pinfo ) ;
 }
 else {
 if ( attrmask & PVFS_ATTR_DATA_SIZE ) {
 offset = dissect_pvfs_uint64 ( tvb , attr_tree , offset , hf_pvfs_size , NULL ) ;
 }
 else {
 if ( attrmask & PVFS_ATTR_SYMLNK_TARGET ) {
 proto_tree_add_item ( attr_tree , hf_pvfs_target_path_len , tvb , offset , 4 , ENC_LITTLE_ENDIAN ) ;
 offset += 4 ;
 offset += 4 ;
 offset = dissect_pvfs_string ( tvb , attr_tree , hf_pvfs_path , offset , NULL ) ;
 }
 else {
 if ( attrmask & PVFS_ATTR_DIR_DIRENT_COUNT ) {
 offset = dissect_pvfs_uint64 ( tvb , attr_tree , offset , hf_pvfs_size , NULL ) ;
 }
 }
 }
 }
 }
 return offset ;
 }