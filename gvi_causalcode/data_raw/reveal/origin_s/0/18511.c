static pvfs2_io_tracking_value_t * pvfs2_io_tracking_new_with_tag ( guint64 tag , guint32 num ) {
 pvfs2_io_tracking_value_t * value ;
 pvfs2_io_tracking_key_t * newkey ;
 newkey = wmem_new0 ( wmem_file_scope ( ) , pvfs2_io_tracking_key_t ) ;
 newkey -> tag = tag ;
 value = wmem_new0 ( wmem_file_scope ( ) , pvfs2_io_tracking_value_t ) ;
 wmem_map_insert ( pvfs2_io_tracking_value_table , newkey , value ) ;
 value -> request_frame_num = num ;
 return value ;
 }