static smb_fid_info_t * find_fid_info ( smb_info_t * si ) {
 smb_fid_info_t * fid_info = NULL ;
 smb_transact_info_t * tri = ( smb_transact_info_t * ) ( ( si -> sip && ( si -> sip -> extra_info_type == SMB_EI_TRI ) ) ? si -> sip -> extra_info : NULL ) ;
 GSList * iter ;
 guint32 fid = 0 ;
 if ( tri == NULL ) {
 if ( si -> sip && ( si -> sip -> extra_info_type == SMB_EI_RWINFO ) ) {
 fid = si -> sip -> fid ;
 }
 }
 else {
 fid = tri -> fid ;
 }
 if ( ! fid ) {
 return NULL ;
 }
 for ( iter = si -> ct -> GSL_fid_info ;
 iter ;
 iter = iter -> next ) {
 smb_fid_info_t * info = ( smb_fid_info_t * ) iter -> data ;
 if ( ( info -> tid == si -> tid ) && ( info -> fid == fid ) ) {
 fid_info = info ;
 break ;
 }
 }
 return fid_info ;
 }