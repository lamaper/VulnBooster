static gboolean dissect_pvfs_common ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * parent_tree , gboolean dissect_other_as_continuation _U_ ) {
 guint32 mode = 0 ;
 proto_item * item ;
 proto_tree * pvfs_tree = NULL , * pvfs_htree = NULL ;
 int offset = 0 ;
 guint64 tag ;
 guint32 server_op ;
 pvfs2_io_tracking_value_t * val = NULL ;
 col_set_str ( pinfo -> cinfo , COL_PROTOCOL , "PVFS" ) ;
 col_clear ( pinfo -> cinfo , COL_INFO ) ;
 item = proto_tree_add_item ( parent_tree , proto_pvfs , tvb , 0 , - 1 , ENC_NA ) ;
 pvfs_tree = proto_item_add_subtree ( item , ett_pvfs ) ;
 proto_tree_add_item ( pvfs_tree , hf_pvfs_version2 , tvb , 0 , - 1 , ENC_NA ) ;
 pvfs_htree = proto_tree_add_subtree ( pvfs_tree , tvb , 0 , BMI_HEADER_SIZE , ett_pvfs_hdr , NULL , "BMI Header" ) ;
 proto_tree_add_item ( pvfs_htree , hf_pvfs_magic_nr , tvb , offset , 4 , ENC_LITTLE_ENDIAN ) ;
 offset += 4 ;
 mode = tvb_get_letohl ( tvb , offset ) ;
 proto_tree_add_uint ( pvfs_htree , hf_pvfs_mode , tvb , offset , 4 , mode ) ;
 offset += 4 ;
 offset = dissect_pvfs_uint64 ( tvb , pvfs_htree , offset , hf_pvfs_tag , & tag ) ;
 offset = dissect_pvfs_uint64 ( tvb , pvfs_htree , offset , hf_pvfs_size , NULL ) ;
 server_op = tvb_get_letohl ( tvb , offset + 8 ) ;
 if ( mode == TCP_MODE_UNEXP ) {
 if ( ( server_op == PVFS_SERV_IO ) && ! pinfo -> fd -> flags . visited ) val = pvfs2_io_tracking_new_with_tag ( tag , pinfo -> num ) ;
 }
 else {
 pvfs2_io_tracking_key_t key ;
 memset ( & key , 0 , sizeof ( key ) ) ;
 key . tag = tag ;
 val = ( pvfs2_io_tracking_value_t * ) wmem_map_lookup ( pvfs2_io_tracking_value_table , & key ) ;
 if ( val && ! pinfo -> fd -> flags . visited ) {
 if ( val -> response_frame_num == 0 ) val -> response_frame_num = pinfo -> num ;
 else {
 if ( val -> flow_frame_num == 0 ) val -> flow_frame_num = pinfo -> num ;
 }
 }
 }
 if ( val && ( val -> flow_frame_num == pinfo -> num ) ) {
 col_set_str ( pinfo -> cinfo , COL_INFO , "PVFS flow data" ) ;
 proto_tree_add_item ( pvfs_tree , hf_pvfs_flow_data , tvb , offset , - 1 , ENC_NA ) ;
 return TRUE ;
 }
 offset = dissect_pvfs2_common_header ( tvb , pvfs_htree , offset ) ;
 col_add_str ( pinfo -> cinfo , COL_INFO , val_to_str ( server_op , names_pvfs_server_op , "%u (unknown)" ) ) ;
 col_append_str ( pinfo -> cinfo , COL_INFO , ( mode == TCP_MODE_UNEXP ) ? " (request)" : " (response)" ) ;
 if ( mode == TCP_MODE_UNEXP ) {
 dissect_pvfs2_request ( tvb , pvfs_tree , offset , pinfo , server_op ) ;
 }
 else {

 col_set_str ( pinfo -> cinfo , COL_INFO , "PVFS2 DATA (request)" ) ;
 }
 else # endif {
 dissect_pvfs2_response ( tvb , pvfs_tree , offset , pinfo , server_op ) ;
 }
 }
 return TRUE ;
 }