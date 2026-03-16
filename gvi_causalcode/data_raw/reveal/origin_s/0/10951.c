static int dissect_pvfs2_getconfig_response ( tvbuff_t * tvb , proto_tree * parent_tree , int offset , packet_info * pinfo ) {
 guint32 i ;
 guint32 total_bytes = 0 , total_config_bytes = 0 , total_lines = 0 ;
 guint32 bytes_processed = 0 ;
 guint32 length_remaining = 0 ;
 const char * ptr = NULL ;
 proto_tree * tree , * config_tree = NULL ;
 tree = proto_tree_add_subtree ( parent_tree , tvb , offset , 12 , ett_pvfs_server_config , NULL , "Server Config" ) ;
 total_bytes = tvb_get_letohl ( tvb , offset ) ;
 proto_tree_add_item ( tree , hf_pvfs_getconfig_response_total_bytes , tvb , offset , 4 , ENC_LITTLE_ENDIAN ) ;
 offset += 4 ;
 if ( total_bytes < 4 ) {
 return offset ;
 }
 total_lines = tvb_get_letohl ( tvb , offset ) ;
 proto_tree_add_item ( tree , hf_pvfs_getconfig_response_lines , tvb , offset , 4 , ENC_LITTLE_ENDIAN ) ;
 offset += 4 ;
 total_config_bytes = tvb_get_letohl ( tvb , offset ) ;
 proto_tree_add_item ( tree , hf_pvfs_getconfig_response_config_bytes , tvb , offset , 4 , ENC_LITTLE_ENDIAN ) ;
 offset += 4 ;
 ptr = tvb_get_ptr ( tvb , offset , total_config_bytes ) ;
 if ( ! ptr ) {
 return offset ;
 }
 length_remaining = tvb_captured_length_remaining ( tvb , offset ) ;
 if ( length_remaining < total_config_bytes ) {
 total_config_bytes = length_remaining ;
 }
 bytes_processed = 0 ;
 for ( i = 0 ;
 i < total_lines ;
 i ++ ) {
 guint8 entry [ 256 ] , * pentry = entry , * tmp_entry = NULL ;
 guint32 entry_length = 0 , tmp_entry_length = 0 ;
 guint32 bufsiz = sizeof ( entry ) ;
 while ( ( * ptr != '\n' ) && ( * ptr != '\0' ) && ( bytes_processed < total_config_bytes ) && ( entry_length < bufsiz ) ) {
 * pentry ++ = * ptr ++ ;
 bytes_processed ++ ;
 entry_length ++ ;
 }
 if ( ( entry_length == bufsiz ) && ( ( entry [ entry_length - 1 ] != '\n' ) && ( entry [ entry_length - 1 ] != '\0' ) ) ) {
 break ;
 }
 if ( bytes_processed == total_config_bytes ) {
 break ;
 }
 * pentry = '\0' ;
 tmp_entry = entry ;
 tmp_entry_length = entry_length ;
 while ( ( tmp_entry_length > 0 ) && ( ! g_ascii_isalnum ( * tmp_entry ) ) && ( * tmp_entry != '<' ) ) {
 tmp_entry ++ ;
 tmp_entry_length -- ;
 }
 if ( tmp_entry [ 0 ] == '<' ) {
 if ( tmp_entry [ tmp_entry_length - 1 ] == '>' ) {
 if ( tmp_entry [ 1 ] != '/' ) {
 config_tree = proto_tree_add_subtree ( tree , tvb , offset , tmp_entry_length , ett_pvfs_server_config_branch , NULL , tmp_entry ) ;
 }
 else {
 config_tree = NULL ;
 }
 }
 else {
 break ;
 }
 }
 else {
 if ( config_tree == NULL ) config_tree = tree ;
 if ( tmp_entry_length > 0 ) {
 proto_tree_add_string_format ( config_tree , hf_pvfs_getconfig_response_entry , tvb , offset , tmp_entry_length , tmp_entry , "%s" , tmp_entry ) ;
 }
 }
 offset += entry_length + 1 ;
 ptr ++ ;
 bytes_processed ++ ;
 }
 if ( bytes_processed < total_config_bytes ) {
 proto_tree_add_expert ( config_tree , pinfo , & ei_pvfs_malformed , tvb , offset , - 1 ) ;
 }
 return offset ;
 }