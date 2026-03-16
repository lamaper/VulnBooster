static int dissect_pvfs2_lookup_path_response ( tvbuff_t * tvb , proto_tree * tree , int offset , packet_info * pinfo ) {
 guint32 nCount = 0 ;
 guint32 handle_count = 0 ;
 guint32 attr_count = 0 ;
 proto_tree * attr_tree ;
 offset += 4 ;
 handle_count = tvb_get_letohl ( tvb , offset ) ;
 proto_tree_add_item ( tree , hf_pvfs_lookup_path_response_handle_count , tvb , offset , 4 , ENC_LITTLE_ENDIAN ) ;
 offset += 4 ;
 for ( nCount = 0 ;
 nCount < handle_count ;
 nCount ++ ) offset = dissect_pvfs_fh ( tvb , offset , pinfo , tree , "handle" , NULL ) ;
 offset += 4 ;
 attr_count = tvb_get_letohl ( tvb , offset ) ;
 attr_tree = proto_tree_add_subtree_format ( tree , tvb , offset , 4 , ett_pvfs_attr , NULL , "Attribute array (total items: %d)" , attr_count ) ;
 offset += 4 ;
 for ( nCount = 0 ;
 nCount < attr_count ;
 nCount ++ ) offset = dissect_pvfs_object_attr ( tvb , attr_tree , offset , pinfo ) ;
 return offset ;
 }