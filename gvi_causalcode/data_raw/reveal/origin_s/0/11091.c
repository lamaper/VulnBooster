static int dissect_pvfs2_mgmt_dspace_info ( tvbuff_t * tvb , proto_tree * tree , int offset , packet_info * pinfo ) {
 offset = dissect_pvfs2_error ( tvb , tree , offset , pinfo ) ;
 offset = dissect_pvfs_fh ( tvb , offset , pinfo , tree , "handle" , NULL ) ;
 offset = dissect_pvfs2_ds_type ( tvb , tree , offset , NULL ) ;
 offset = dissect_pvfs_uint64 ( tvb , tree , offset , hf_pvfs_b_size , NULL ) ;
 offset = dissect_pvfs_uint64 ( tvb , tree , offset , hf_pvfs_k_size , NULL ) ;
 offset = dissect_pvfs_fh ( tvb , offset , pinfo , tree , "handle" , NULL ) ;
 return offset ;
 }