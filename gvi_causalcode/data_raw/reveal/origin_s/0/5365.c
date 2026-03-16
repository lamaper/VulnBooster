static int dissect_mswsp_smb ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , void * data ) {
 smb_info_t * si = ( smb_info_t * ) data ;
 gboolean in = si -> request ;
 smb_fid_info_t * fid_info = NULL ;
 fid_info = find_fid_info ( si ) ;
 if ( ! fid_info || ! fid_info -> fsi || ! fid_info -> fsi -> filename ) {
 return 0 ;
 }
 if ( g_ascii_strcasecmp ( fid_info -> fsi -> filename , "\\MsFteWds" ) != 0 ) {
 return 0 ;
 }
 p_add_proto_data ( wmem_file_scope ( ) , pinfo , proto_mswsp , 0 , ( void * ) & SMB1 ) ;
 return dissect_mswsp ( tvb , pinfo , tree , in , data ) ;
 }