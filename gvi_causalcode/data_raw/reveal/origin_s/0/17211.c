static int dissect_pvfs2_mgmt_get_dirdata_handle_response ( tvbuff_t * tvb , proto_tree * tree , int offset , packet_info * pinfo ) {
 offset = dissect_pvfs_fh ( tvb , offset , pinfo , tree , "handle" , NULL ) ;
 return offset ;
 }