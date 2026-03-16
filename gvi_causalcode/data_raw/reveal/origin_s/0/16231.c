static int dissect_pvfs2_ds_type ( tvbuff_t * tvb , proto_tree * tree , int offset , int * pds_type ) {
 guint32 ds_type ;
 ds_type = tvb_get_letohl ( tvb , offset ) ;
 proto_tree_add_uint ( tree , hf_pvfs_ds_type , tvb , offset , 4 , ds_type ) ;
 offset += 4 ;
 if ( pds_type ) * pds_type = ds_type ;
 return offset ;
 }