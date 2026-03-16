static gboolean get_fid_and_frame ( packet_info * pinfo , guint32 * fid , guint * frame , void * data ) {
 gboolean result = TRUE ;
 int * p_smb_level = ( int * ) p_get_proto_data ( wmem_file_scope ( ) , pinfo , proto_mswsp , 0 ) ;
 if ( ! p_smb_level ) {
 return FALSE ;
 }
 * frame = pinfo -> num ;
 if ( * p_smb_level == SMB1 ) {
 smb_info_t * si = ( smb_info_t * ) data ;
 smb_fid_info_t * info ;
 info = find_fid_info ( si ) ;
 if ( ! info ) {
 return FALSE ;
 }
 * fid = info -> fid ;
 }
 else {
 smb2_info_t * si2 = ( smb2_info_t * ) data ;
 guint32 open_frame = 0 , close_frame = 0 ;
 char * fid_name = NULL ;
 if ( si2 -> saved ) {
 dcerpc_fetch_polhnd_data ( & si2 -> saved -> policy_hnd , & fid_name , NULL , & open_frame , & close_frame , pinfo -> num ) ;
 * fid = open_frame ;
 }
 else {
 result = FALSE ;
 }
 }
 return result ;
 }