static int dissect_pvfs2_request ( tvbuff_t * tvb , proto_tree * tree , int offset , packet_info * pinfo , guint32 server_op ) {
 proto_tree_add_item ( tree , hf_pvfs_context_id , tvb , offset , 4 , ENC_LITTLE_ENDIAN ) ;
 offset += 4 ;
 offset = dissect_pvfs_credentials ( tvb , tree , offset ) ;
 switch ( server_op ) {
 case PVFS_SERV_CREATE : offset = dissect_pvfs2_create_request ( tvb , tree , offset , pinfo ) ;
 break ;
 case PVFS_SERV_REMOVE : offset = dissect_pvfs2_remove_request ( tvb , tree , offset , pinfo ) ;
 break ;
 case PVFS_SERV_IO : offset = dissect_pvfs2_io_request ( tvb , tree , offset , pinfo ) ;
 break ;
 case PVFS_SERV_GETATTR : offset = dissect_pvfs2_getattr_request ( tvb , tree , offset , pinfo ) ;
 break ;
 case PVFS_SERV_SETATTR : offset = dissect_pvfs2_setattr_request ( tvb , tree , offset , pinfo ) ;
 break ;
 case PVFS_SERV_LOOKUP_PATH : offset = dissect_pvfs2_lookup_path_request ( tvb , tree , offset , pinfo ) ;
 break ;
 case PVFS_SERV_CRDIRENT : offset = dissect_pvfs2_crdirent_request ( tvb , tree , offset , pinfo ) ;
 break ;
 case PVFS_SERV_RMDIRENT : offset = dissect_pvfs2_rmdirent_request ( tvb , tree , offset , pinfo ) ;
 break ;
 case PVFS_SERV_CHDIRENT : offset = dissect_pvfs2_chdirent_request ( tvb , tree , offset , pinfo ) ;
 break ;
 case PVFS_SERV_TRUNCATE : offset = dissect_pvfs2_truncate_request ( tvb , tree , offset , pinfo ) ;
 break ;
 case PVFS_SERV_MKDIR : offset = dissect_pvfs2_mkdir_request ( tvb , tree , offset , pinfo ) ;
 break ;
 case PVFS_SERV_READDIR : offset = dissect_pvfs2_readdir_request ( tvb , tree , offset , pinfo ) ;
 break ;



 break ;
 case PVFS_SERV_MGMT_SETPARAM : offset = dissect_pvfs2_mgmt_setparam_request ( tvb , tree , offset , pinfo ) ;
 break ;


 break ;


 break ;
 case PVFS_SERV_MGMT_ITERATE_HANDLES : offset = dissect_pvfs2_mgmt_iterate_handles_request ( tvb , tree , offset , pinfo ) ;
 break ;
 case PVFS_SERV_MGMT_DSPACE_INFO_LIST : offset = dissect_pvfs2_mgmt_dspace_info_list_request ( tvb , tree , offset , pinfo ) ;
 break ;
 case PVFS_SERV_MGMT_EVENT_MON : offset = dissect_pvfs2_mgmt_event_mon_request ( tvb , tree , offset , pinfo ) ;
 break ;
 case PVFS_SERV_MGMT_REMOVE_OBJECT : offset = dissect_pvfs2_mgmt_remove_object_request ( tvb , tree , offset , pinfo ) ;
 break ;
 case PVFS_SERV_MGMT_REMOVE_DIRENT : offset = dissect_pvfs2_mgmt_remove_dirent_request ( tvb , tree , offset , pinfo ) ;
 break ;
 case PVFS_SERV_MGMT_GET_DIRDATA_HANDLE : offset = dissect_pvfs2_mgmt_get_dirdata_handle_request ( tvb , tree , offset , pinfo ) ;
 break ;


 case PVFS_SERV_GETEATTR : offset = dissect_pvfs2_geteattr_request ( tvb , tree , offset , pinfo ) ;
 break ;
 case PVFS_SERV_SETEATTR : offset = dissect_pvfs2_seteattr_request ( tvb , tree , offset , pinfo ) ;
 break ;
 case PVFS_SERV_DELEATTR : offset = dissect_pvfs2_deleattr_request ( tvb , tree , offset , pinfo ) ;
 break ;
 default : break ;
 }
 return offset ;
 }