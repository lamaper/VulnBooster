static int dissect_pvfs2_mgmt_dspace_info_list_request ( tvbuff_t * tvb , proto_tree * tree , int offset , packet_info * pinfo ) {
 guint32 handle_count , i ;
 offset = dissect_pvfs_fs_id ( tvb , tree , offset ) ;
 handle_count = tvb_get_letohl ( tvb , offset ) ;
 offset += 4 ;
 for ( i = 0 ;
 i < handle_count ;
 i ++ ) {
 offset = dissect_pvfs_fh ( tvb , offset , pinfo , tree , "handle" , NULL ) ;
 }
 return offset ;
 }