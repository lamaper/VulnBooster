static int dissect_pvfs2_mgmt_dspace_info_list_response ( tvbuff_t * tvb , proto_tree * tree , int offset , packet_info * pinfo ) {
 guint32 dspace_info_count , i ;
 proto_tree * arr_tree = NULL ;
 offset += 4 ;
 dspace_info_count = tvb_get_letohl ( tvb , offset ) ;
 proto_tree_add_item ( tree , hf_pvfs_mgmt_dspace_info_list_response_dspace_info_count , tvb , offset , 4 , ENC_LITTLE_ENDIAN ) ;
 if ( ( dspace_info_count > 0 ) && ( tree ) ) {
 arr_tree = proto_tree_add_subtree_format ( tree , tvb , offset , dspace_info_count * 40 , ett_pvfs_mgmt_dspace_info , NULL , "dspace_info Array (%d items)" , dspace_info_count ) ;
 }
 for ( i = 0 ;
 i < dspace_info_count ;
 i ++ ) offset = dissect_pvfs2_mgmt_dspace_info ( tvb , arr_tree , offset , pinfo ) ;
 return offset ;
 }