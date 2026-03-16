static int dissect_mswsp_smb2 ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , void * data ) {
 smb2_info_t * si = ( smb2_info_t * ) data ;
 gboolean in ;
 char * fid_name = NULL ;
 guint32 open_frame = 0 , close_frame = 0 ;
 if ( ! si ) {
 return 0 ;
 }
 if ( si -> saved ) {
 dcerpc_fetch_polhnd_data ( & si -> saved -> policy_hnd , & fid_name , NULL , & open_frame , & close_frame , pinfo -> num ) ;
 }
 if ( ! fid_name || strcmp ( fid_name , "File: MsFteWds" ) != 0 ) {
 return 0 ;
 }
 in = ! ( si -> flags & SMB2_FLAGS_RESPONSE ) ;
 p_add_proto_data ( wmem_file_scope ( ) , pinfo , proto_mswsp , 0 , ( void * ) & SMB2 ) ;
 return dissect_mswsp ( tvb , pinfo , tree , in , data ) ;
 }