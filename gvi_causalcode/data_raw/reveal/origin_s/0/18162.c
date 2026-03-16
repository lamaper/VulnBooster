static int dissect_pvfs_credentials ( tvbuff_t * tvb , proto_tree * parent_tree , int offset ) {
 proto_tree * hcred_tree ;
 guint32 uid , gid ;
 uid = tvb_get_letohl ( tvb , offset ) ;
 gid = tvb_get_letohl ( tvb , offset + 4 ) ;
 hcred_tree = proto_tree_add_subtree_format ( parent_tree , tvb , offset , 8 , ett_pvfs_credentials , NULL , "Credentials (UID: %d, GID: %d)" , uid , gid ) ;
 proto_tree_add_item ( hcred_tree , hf_pvfs_uid , tvb , offset , 4 , ENC_LITTLE_ENDIAN ) ;
 offset += 4 ;
 proto_tree_add_item ( hcred_tree , hf_pvfs_gid , tvb , offset , 4 , ENC_LITTLE_ENDIAN ) ;
 offset += 4 ;
 return offset ;
 }