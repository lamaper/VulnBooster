static int dissect_pvfs_ds_keyval ( tvbuff_t * tvb , proto_tree * tree , int offset ) {
 offset = dissect_pvfs_string ( tvb , tree , hf_pvfs_attribute_key , offset , NULL ) ;
 offset = dissect_pvfs_string ( tvb , tree , hf_pvfs_attribute_value , offset , NULL ) ;
 return offset ;
 }