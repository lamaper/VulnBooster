void proto_register_pvfs ( void ) {
 static hf_register_info hf [ ] = {
 {
 & hf_pvfs_magic_nr , {
 "Magic Number" , "pvfs.magic_nr" , FT_UINT32 , BASE_HEX , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_uid , {
 "UID" , "pvfs.uid" , FT_UINT32 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_gid , {
 "GID" , "pvfs.gid" , FT_UINT32 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_mode , {
 "Mode" , "pvfs.mode" , FT_UINT32 , BASE_DEC , VALS ( names_pvfs_mode ) , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_tag , {
 "Tag" , "pvfs.tag" , FT_UINT64 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_size , {
 "Size" , "pvfs.size" , FT_UINT64 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_release_number , {
 "Release Number" , "pvfs.release_number" , FT_UINT32 , BASE_CUSTOM , CF_FUNC ( pvfc_fmt_release_num ) , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_encoding , {
 "Encoding" , "pvfs.encoding" , FT_UINT32 , BASE_DEC , VALS ( names_pvfs_encoding ) , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_server_op , {
 "Server Operation" , "pvfs.server_op" , FT_UINT32 , BASE_DEC , VALS ( names_pvfs_server_op ) , 0 , NULL , HFILL }
 }
 , # if 0 {
 & hf_pvfs_handle , {
 "Handle" , "pvfs.handle" , FT_BYTES , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , # endif {
 & hf_pvfs_fs_id , {
 "fs_id" , "pvfs.fs_id" , FT_UINT32 , BASE_HEX , NULL , 0 , "File System ID" , HFILL }
 }
 , {
 & hf_pvfs_attrmask , {
 "Attribute Mask" , "pvfs.attrmask" , FT_UINT32 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_attr , {
 "attr" , "pvfs.attribute" , FT_UINT32 , BASE_HEX , VALS ( names_pvfs_attr ) , 0 , "Attribute" , HFILL }
 }
 , {
 & hf_pvfs_ds_type , {
 "ds_type" , "pvfs.ds_type" , FT_UINT32 , BASE_HEX , VALS ( names_pvfs_ds_type ) , 0 , "Type" , HFILL }
 }
 , {
 & hf_pvfs_error , {
 "Result" , "pvfs.error" , FT_UINT32 , BASE_HEX , VALS ( names_pvfs_error ) , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_atime , {
 "atime" , "pvfs.atime" , FT_ABSOLUTE_TIME , ABSOLUTE_TIME_LOCAL , NULL , 0 , "Access Time" , HFILL }
 }
 , {
 & hf_pvfs_atime_sec , {
 "seconds" , "pvfs.atime.sec" , FT_UINT32 , BASE_DEC , NULL , 0 , "Access Time (seconds)" , HFILL }
 }
 , {
 & hf_pvfs_atime_nsec , {
 "microseconds" , "pvfs.atime.usec" , FT_UINT32 , BASE_DEC , NULL , 0 , "Access Time (microseconds)" , HFILL }
 }
 , {
 & hf_pvfs_mtime , {
 "mtime" , "pvfs.mtime" , FT_ABSOLUTE_TIME , ABSOLUTE_TIME_LOCAL , NULL , 0 , "Modify Time" , HFILL }
 }
 , {
 & hf_pvfs_mtime_sec , {
 "seconds" , "pvfs.mtime.sec" , FT_UINT32 , BASE_DEC , NULL , 0 , "Modify Time (seconds)" , HFILL }
 }
 , {
 & hf_pvfs_mtime_nsec , {
 "microseconds" , "pvfs.mtime.usec" , FT_UINT32 , BASE_DEC , NULL , 0 , "Modify Time (microseconds)" , HFILL }
 }
 , {
 & hf_pvfs_ctime , {
 "ctime" , "pvfs.ctime" , FT_ABSOLUTE_TIME , ABSOLUTE_TIME_LOCAL , NULL , 0 , "Creation Time" , HFILL }
 }
 , {
 & hf_pvfs_ctime_sec , {
 "seconds" , "pvfs.ctime.sec" , FT_UINT32 , BASE_DEC , NULL , 0 , "Creation Time (seconds)" , HFILL }
 }
 , {
 & hf_pvfs_ctime_nsec , {
 "microseconds" , "pvfs.ctime.usec" , FT_UINT32 , BASE_DEC , NULL , 0 , "Creation Time (microseconds)" , HFILL }
 }
 , {
 & hf_pvfs_parent_atime , {
 "Parent atime" , "pvfs.parent_atime" , FT_ABSOLUTE_TIME , ABSOLUTE_TIME_LOCAL , NULL , 0 , "Access Time" , HFILL }
 }
 , {
 & hf_pvfs_parent_atime_sec , {
 "seconds" , "pvfs.parent_atime.sec" , FT_UINT32 , BASE_DEC , NULL , 0 , "Access Time (seconds)" , HFILL }
 }
 , {
 & hf_pvfs_parent_atime_nsec , {
 "microseconds" , "pvfs.parent_atime.usec" , FT_UINT32 , BASE_DEC , NULL , 0 , "Access Time (microseconds)" , HFILL }
 }
 , {
 & hf_pvfs_parent_mtime , {
 "Parent mtime" , "pvfs.parent_mtime" , FT_ABSOLUTE_TIME , ABSOLUTE_TIME_LOCAL , NULL , 0 , "Modify Time" , HFILL }
 }
 , {
 & hf_pvfs_parent_mtime_sec , {
 "seconds" , "pvfs.parent_mtime.sec" , FT_UINT32 , BASE_DEC , NULL , 0 , "Modify Time (seconds)" , HFILL }
 }
 , {
 & hf_pvfs_parent_mtime_nsec , {
 "microseconds" , "pvfs.parent_mtime.usec" , FT_UINT32 , BASE_DEC , NULL , 0 , "Modify Time (microseconds)" , HFILL }
 }
 , {
 & hf_pvfs_parent_ctime , {
 "Parent ctime" , "pvfs.parent_ctime" , FT_ABSOLUTE_TIME , ABSOLUTE_TIME_LOCAL , NULL , 0 , "Creation Time" , HFILL }
 }
 , {
 & hf_pvfs_parent_ctime_sec , {
 "seconds" , "pvfs.parent_ctime.sec" , FT_UINT32 , BASE_DEC , NULL , 0 , "Creation Time (seconds)" , HFILL }
 }
 , {
 & hf_pvfs_parent_ctime_nsec , {
 "microseconds" , "pvfs.parent_ctime.usec" , FT_UINT32 , BASE_DEC , NULL , 0 , "Creation Time (microseconds)" , HFILL }
 }
 , {
 & hf_pvfs_dfile_count , {
 "dfile_count" , "pvfs.dfile_count" , FT_UINT32 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_distribution , {
 "Distribution" , "pvfs.distribution" , FT_STRING , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_dirent_count , {
 "Dir Entry Count" , "pvfs.dirent_count" , FT_UINT32 , BASE_DEC , NULL , 0 , "Directory Entry Count" , HFILL }
 }
 , {
 & hf_pvfs_directory_version , {
 "Directory Version" , "pvfs.directory_version" , FT_UINT64 , BASE_HEX , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_path , {
 "Path" , "pvfs.path" , FT_STRING , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_total_completed , {
 "Bytes Completed" , "pvfs.bytes_completed" , FT_UINT64 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_io_dist , {
 "Name" , "pvfs.distribution.name" , FT_STRING , BASE_NONE , NULL , 0 , "Distribution Name" , HFILL }
 }
 , {
 & hf_pvfs_aggregate_size , {
 "Aggregate Size" , "pvfs.aggregate_size" , FT_UINT64 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_io_type , {
 "I/O Type" , "pvfs.io_type" , FT_UINT32 , BASE_DEC , VALS ( names_pvfs_io_type ) , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_flowproto_type , {
 "Flow Protocol Type" , "pvfs.flowproto_type" , FT_UINT32 , BASE_DEC , VALS ( names_pvfs_flowproto_type ) , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_server_param , {
 "Server Parameter" , "pvfs.server_param" , FT_UINT32 , BASE_DEC , VALS ( names_pvfs_server_param ) , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_prev_value , {
 "Previous Value" , "pvfs.prev_value" , FT_UINT64 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , # if 0 {
 & hf_pvfs_ram_free_bytes , {
 "RAM Free Bytes" , "pvfs.ram.free_bytes" , FT_UINT64 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , # endif {
 & hf_pvfs_bytes_available , {
 "Bytes Available" , "pvfs.bytes_available" , FT_UINT64 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_bytes_total , {
 "Bytes Total" , "pvfs.bytes_total" , FT_UINT64 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_ram_bytes_total , {
 "RAM Bytes Total" , "pvfs.ram_bytes_total" , FT_UINT64 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_ram_bytes_free , {
 "RAM Bytes Free" , "pvfs.ram_bytes_free" , FT_UINT64 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_load_average_1s , {
 "Load Average (1s)" , "pvfs.load_average.1s" , FT_UINT64 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_load_average_5s , {
 "Load Average (5s)" , "pvfs.load_average.5s" , FT_UINT64 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_load_average_15s , {
 "Load Average (15s)" , "pvfs.load_average.15s" , FT_UINT64 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_uptime_seconds , {
 "Uptime (seconds)" , "pvfs.uptime" , FT_UINT64 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_handles_available , {
 "Handles Available" , "pvfs.handles_available" , FT_UINT64 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_handles_total , {
 "Total Handles" , "pvfs.total_handles" , FT_UINT64 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_unused , {
 "Unused" , "pvfs.unused" , FT_UINT32 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_context_id , {
 "Context ID" , "pvfs.context_id" , FT_UINT32 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_offset , {
 "Offset" , "pvfs.offset" , FT_UINT64 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_stride , {
 "Stride" , "pvfs.stride" , FT_UINT64 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_ub , {
 "ub" , "pvfs.ub" , FT_UINT64 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_lb , {
 "lb" , "pvfs.lb" , FT_UINT64 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_end_time_ms , {
 "end_time_ms" , "pvfs.end_time_ms" , FT_UINT64 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_cur_time_ms , {
 "cur_time_ms" , "pvfs.cur_time_ms" , FT_UINT64 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_start_time_ms , {
 "start_time_ms" , "pvfs.start_time_ms" , FT_UINT64 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_bytes_written , {
 "bytes_written" , "pvfs.bytes_written" , FT_UINT64 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_bytes_read , {
 "bytes_read" , "pvfs.bytes_read" , FT_UINT64 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_metadata_write , {
 "metadata_write" , "pvfs.metadata_write" , FT_UINT64 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_metadata_read , {
 "metadata_read" , "pvfs.metadata_read" , FT_UINT64 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_b_size , {
 "Size of bstream (if applicable)" , "pvfs.b_size" , FT_UINT64 , BASE_DEC , NULL , 0 , "Size of bstream" , HFILL }
 }
 , {
 & hf_pvfs_k_size , {
 "Number of keyvals (if applicable)" , "pvfs.k_size" , FT_UINT64 , BASE_DEC , NULL , 0 , "Number of keyvals" , HFILL }
 }
 , {
 & hf_pvfs_id_gen_t , {
 "id_gen_t" , "pvfs.id_gen_t" , FT_UINT64 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_attribute_key , {
 "Attribute key" , "pvfs.attribute.key" , FT_STRING , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_attribute_value , {
 "Attribute value" , "pvfs.attribute.value" , FT_STRING , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_strip_size , {
 "Strip size" , "pvfs.strip_size" , FT_UINT64 , BASE_DEC , NULL , 0 , "Strip size (bytes)" , HFILL }
 }
 , {
 & hf_pvfs_ereg , {
 "ereg" , "pvfs.ereg" , FT_INT32 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_sreg , {
 "sreg" , "pvfs.sreg" , FT_INT32 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_num_eregs , {
 "Number of eregs" , "pvfs.num_eregs" , FT_UINT32 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_num_blocks , {
 "Number of blocks" , "pvfs.num_blocks" , FT_UINT32 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_num_contig_chunks , {
 "Number of contig_chunks" , "pvfs.num_contig_chunks" , FT_UINT32 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_server_nr , {
 "Server #" , "pvfs.server_nr" , FT_UINT32 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_server_count , {
 "Number of servers" , "pvfs.server_count" , FT_UINT32 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_fh_length , {
 "length" , "pvfs.fh.length" , FT_UINT32 , BASE_DEC , NULL , 0 , "file handle length" , HFILL }
 }
 , {
 & hf_pvfs_fh_hash , {
 "hash" , "pvfs.fh.hash" , FT_UINT32 , BASE_HEX , NULL , 0 , "file handle hash" , HFILL }
 }
 , {
 & hf_pvfs_permissions , {
 "Permissions" , "pvfs.permissions" , FT_UINT32 , BASE_OCT , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_server_mode , {
 "Server Mode" , "pvfs.server_mode" , FT_UINT32 , BASE_DEC , VALS ( names_pvfs_server_mode ) , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_depth , {
 "depth" , "pvfs.depth" , FT_UINT32 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_num_nested_req , {
 "num_nested_req" , "pvfs.num_nested_req" , FT_UINT32 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_committed , {
 "committed" , "pvfs.committed" , FT_UINT32 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_refcount , {
 "refcount" , "pvfs.refcount" , FT_UINT32 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_numreq , {
 "numreq" , "pvfs.numreq" , FT_UINT32 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_truncate_request_flags , {
 "flags" , "pvfs.truncate_request_flags" , FT_UINT32 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_ds_position , {
 "ds_position" , "pvfs.ds_position" , FT_UINT32 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_dirent_limit , {
 "dirent_limit" , "pvfs.dirent_limit" , FT_UINT32 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_flush_request_flags , {
 "flags" , "pvfs.flush_request_flags" , FT_UINT32 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_next_id , {
 "next_id" , "pvfs.next_id" , FT_UINT32 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_mgmt_perf_mon_request_count , {
 "count" , "pvfs.mgmt_perf_mon_request.count" , FT_UINT32 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_mgmt_perf_mon_request_event_count , {
 "Event count" , "pvfs.mgmt_perf_mon_request.event_count" , FT_UINT32 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_lookup_path_response_handle_count , {
 "Handle Count" , "pvfs.lookup_path_response.handle_count" , FT_UINT32 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_getconfig_response_total_bytes , {
 "Total Bytes" , "pvfs.getconfig_response.total_bytes" , FT_UINT32 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_getconfig_response_lines , {
 "Lines" , "pvfs.getconfig_response.lines" , FT_UINT32 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_getconfig_response_config_bytes , {
 "Config Bytes" , "pvfs.getconfig_response.config_bytes" , FT_UINT32 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_mgmt_perf_stat_valid_flag , {
 "valid_flag" , "pvfs.mgmt_perf_stat.valid_flag" , FT_UINT32 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_mgmt_perf_stat_id , {
 "id" , "pvfs.mgmt_perf_stat.id" , FT_UINT32 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_mgmt_perf_mon_response_suggested_next_id , {
 "suggested_next_id" , "pvfs.mgmt_perf_mon_response.suggested_next_id" , FT_UINT32 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_mgmt_perf_mon_response_perf_array_count , {
 "perf_array_count" , "pvfs.mgmt_perf_mon_response.perf_array_count" , FT_UINT32 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_mgmt_iterate_handles_response_ds_position , {
 "ds_position" , "pvfs.mgmt_iterate_handles_response.ds_position" , FT_UINT32 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_mgmt_iterate_handles_response_handle_count , {
 "handle_count" , "pvfs.mgmt_iterate_handles_response.handle_count" , FT_UINT32 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_mgmt_dspace_info_list_response_dspace_info_count , {
 "dspace_info_count" , "pvfs.mgmt_dspace_info_list_response.dspace_info_count" , FT_UINT32 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_mgmt_event_mon_response_api , {
 "api" , "pvfs.mgmt_event_mon_response.api" , FT_UINT32 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_mgmt_event_mon_response_operation , {
 "operation" , "pvfs.mgmt_event_mon_response.operation" , FT_UINT32 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_mgmt_event_mon_response_value , {
 "value" , "pvfs.mgmt_event_mon_response.value" , FT_UINT32 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_mgmt_event_mon_response_flags , {
 "flags" , "pvfs.mgmt_event_mon_response.flags" , FT_UINT32 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_mgmt_event_mon_response_tv_sec , {
 "tv_sec" , "pvfs.mgmt_event_mon_response.tv_sec" , FT_UINT32 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_mgmt_event_mon_response_tv_usec , {
 "tv_usec" , "pvfs.mgmt_event_mon_response.tv_usec" , FT_UINT32 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_fill_bytes , {
 "fill_bytes" , "pvfs.fill_bytes" , FT_BYTES , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_target_path_len , {
 "target_path_len" , "pvfs.target_path_len" , FT_UINT32 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_version2 , {
 "Version 2" , "pvfs.version2" , FT_NONE , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_flow_data , {
 "PVFC Flow Data" , "pvfs.flow_data" , FT_BYTES , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_getconfig_response_entry , {
 "GETCONFIG Response entry" , "pvfs.getconfig_response_entry" , FT_STRING , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_fhandle_data , {
 "data" , "pvfs.fhandle_data" , FT_BYTES , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_pvfs_opaque_length , {
 "length" , "pvfs.opaque_length" , FT_UINT32 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , }
 ;
 static gint * ett [ ] = {
 & ett_pvfs , & ett_pvfs_hdr , & ett_pvfs_credentials , & ett_pvfs_server_config , & ett_pvfs_server_config_branch , & ett_pvfs_attrmask , & ett_pvfs_time , & ett_pvfs_extent_array_tree , & ett_pvfs_extent_item , & ett_pvfs_string , & ett_pvfs_attr_tree , & ett_pvfs_distribution , & ett_pvfs_mgmt_perf_stat , & ett_pvfs_mgmt_dspace_info , & ett_pvfs_attr , & ett_pvfs_fh }
 ;
 static ei_register_info ei [ ] = {
 {
 & ei_pvfs_malformed , {
 "pvfs.malformed" , PI_MALFORMED , PI_ERROR , "MALFORMED OR TRUNCATED DATA" , EXPFILL }
 }
 , }
 ;
 module_t * pvfs_module ;
 expert_module_t * expert_pvfs ;
 proto_pvfs = proto_register_protocol ( "Parallel Virtual File System" , "PVFS" , "pvfs" ) ;
 proto_register_field_array ( proto_pvfs , hf , array_length ( hf ) ) ;
 proto_register_subtree_array ( ett , array_length ( ett ) ) ;
 expert_pvfs = expert_register_protocol ( proto_pvfs ) ;
 expert_register_field_array ( expert_pvfs , ei , array_length ( ei ) ) ;
 pvfs2_io_tracking_value_table = wmem_map_new_autoreset ( wmem_epan_scope ( ) , wmem_file_scope ( ) , pvfs2_io_tracking_hash , pvfs2_io_tracking_equal ) ;
 pvfs_module = prefs_register_protocol ( proto_pvfs , NULL ) ;
 prefs_register_bool_preference ( pvfs_module , "desegment" , "Reassemble PVFS messages spanning multiple TCP segments" , "Whether the PVFS dissector should reassemble messages spanning multiple TCP segments. " "To use this option, you must also enable \"Allow subdissectors to reassemble TCP streams\" in the TCP protocol settings." , & pvfs_desegment ) ;
 }