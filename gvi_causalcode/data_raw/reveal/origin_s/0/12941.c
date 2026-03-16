static int dissect_pvfs2_mgmt_iterate_handles_response ( tvbuff_t * tvb , proto_tree * tree , int offset , packet_info * pinfo ) {
 guint32 handle_count , i ;
 proto_tree_add_item ( tree , hf_pvfs_mgmt_iterate_handles_response_ds_position , tvb , offset , 4 , ENC_LITTLE_ENDIAN ) ;
 offset += 4 ;
 handle_count = tvb_get_letohl ( tvb , offset ) ;
 proto_tree_add_item ( tree , hf_pvfs_mgmt_iterate_handles_response_handle_count , tvb , offset , 4 , ENC_LITTLE_ENDIAN ) ;
 offset += 4 ;
 for ( i = 0 ;
 i < handle_count ;
 i ++ ) offset = dissect_pvfs_fh ( tvb , offset , pinfo , tree , "handle" , NULL ) ;
 return offset ;
 }