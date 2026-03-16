static int dissect_pvfs_mgmt_perf_stat ( tvbuff_t * tvb , proto_tree * tree , int offset , int nItem ) {
 proto_tree * stat_tree ;
 stat_tree = proto_tree_add_subtree_format ( tree , tvb , offset , 48 , ett_pvfs_mgmt_perf_stat , NULL , "Stat Array - Element %d" , nItem ) ;
 proto_tree_add_item ( stat_tree , hf_pvfs_mgmt_perf_stat_valid_flag , tvb , offset , 4 , ENC_LITTLE_ENDIAN ) ;
 offset += 4 ;
 proto_tree_add_item ( stat_tree , hf_pvfs_mgmt_perf_stat_id , tvb , offset , 4 , ENC_LITTLE_ENDIAN ) ;
 offset += 4 ;
 offset = dissect_pvfs_uint64 ( tvb , stat_tree , offset , hf_pvfs_start_time_ms , NULL ) ;
 offset = dissect_pvfs_uint64 ( tvb , stat_tree , offset , hf_pvfs_bytes_written , NULL ) ;
 offset = dissect_pvfs_uint64 ( tvb , stat_tree , offset , hf_pvfs_bytes_read , NULL ) ;
 offset = dissect_pvfs_uint64 ( tvb , stat_tree , offset , hf_pvfs_metadata_write , NULL ) ;
 offset = dissect_pvfs_uint64 ( tvb , stat_tree , offset , hf_pvfs_metadata_read , NULL ) ;
 return offset ;
 }