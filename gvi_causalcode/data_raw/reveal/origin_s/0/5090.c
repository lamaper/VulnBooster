static int dissect_pvfs_server_param ( tvbuff_t * tvb , proto_tree * tree , int offset , packet_info * pinfo ) {
 guint32 server_param ;
 proto_item * ti ;
 server_param = tvb_get_letohl ( tvb , offset ) ;
 proto_tree_add_uint ( tree , hf_pvfs_server_param , tvb , offset , 4 , server_param ) ;
 offset += 4 ;
 switch ( server_param ) {
 case PVFS_SERV_PARAM_MODE : ti = proto_tree_add_item ( tree , hf_pvfs_server_mode , tvb , offset , 4 , ENC_LITTLE_ENDIAN ) ;
 proto_item_set_len ( ti , 8 ) ;
 break ;
 case PVFS_SERV_PARAM_FSID_CHECK : proto_tree_add_item ( tree , hf_pvfs_fs_id , tvb , offset , 4 , ENC_LITTLE_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_pvfs_unused , tvb , offset + 4 , 4 , ENC_LITTLE_ENDIAN ) ;
 break ;
 case PVFS_SERV_PARAM_ROOT_CHECK : offset = dissect_pvfs_fh ( tvb , offset , pinfo , tree , "handle" , NULL ) ;
 break ;
 }
 offset += 8 ;
 return offset ;
 }