static int dissect_pvfs2_io_request ( tvbuff_t * tvb , proto_tree * tree , int offset , packet_info * pinfo ) {
 offset = dissect_pvfs_fh ( tvb , offset , pinfo , tree , "handle" , NULL ) ;
 offset = dissect_pvfs_fs_id ( tvb , tree , offset ) ;
 offset += 4 ;
 offset = dissect_pvfs_io_type ( tvb , tree , offset ) ;
 offset = dissect_pvfs_flowproto_type ( tvb , tree , offset ) ;
 proto_tree_add_item ( tree , hf_pvfs_server_nr , tvb , offset , 4 , ENC_LITTLE_ENDIAN ) ;
 offset += 4 ;
 proto_tree_add_item ( tree , hf_pvfs_server_count , tvb , offset , 4 , ENC_LITTLE_ENDIAN ) ;
 offset += 4 ;
 offset = dissect_pvfs_distribution ( tvb , tree , offset ) ;
 proto_tree_add_item ( tree , hf_pvfs_numreq , tvb , offset , 4 , ENC_LITTLE_ENDIAN ) ;
 offset += 4 ;
 offset += 4 ;
 dissect_pvfs_pint_request ( tvb , tree , offset ) ;
 offset = tvb_reported_length ( tvb ) - 16 ;
 proto_tree_add_item ( tree , hf_pvfs_offset , tvb , offset , 8 , ENC_LITTLE_ENDIAN ) ;
 offset += 8 ;
 proto_tree_add_item ( tree , hf_pvfs_size , tvb , offset , 8 , ENC_LITTLE_ENDIAN ) ;
 offset += 8 ;
 return offset ;
 }