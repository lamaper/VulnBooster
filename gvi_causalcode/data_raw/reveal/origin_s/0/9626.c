static int dissect_pvfs_meta_attr_dfiles ( tvbuff_t * tvb , proto_tree * tree , int offset , packet_info * pinfo ) {
 guint32 dfile_count , i ;
 dfile_count = tvb_get_letohl ( tvb , offset ) ;
 proto_tree_add_uint ( tree , hf_pvfs_dfile_count , tvb , offset , 4 , dfile_count ) ;
 offset += 4 ;
 for ( i = 0 ;
 i < dfile_count ;
 i ++ ) offset = dissect_pvfs_fh ( tvb , offset , pinfo , tree , "handle" , NULL ) ;
 return offset ;
 }