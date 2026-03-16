static struct message_data * find_matching_request_by_fid ( struct mswsp_ct * ct , packet_info * pinfo , guint32 msg , gboolean in , void * private_data ) {
 guint32 fid = 0 ;
 guint frame = 0 ;
 GSList * iter ;
 int * p_smb_level = ( int * ) p_get_proto_data ( wmem_file_scope ( ) , pinfo , proto_mswsp , 0 ) ;
 struct message_data * result = NULL ;
 get_fid_and_frame ( pinfo , & fid , & frame , private_data ) ;
 for ( iter = ct -> GSL_message_data ;
 iter ;
 iter = iter -> next ) {
 struct message_data * data = ( struct message_data * ) iter -> data ;
 if ( data -> frame < frame && data -> fid == fid && data -> is_request == in && data -> msg_id == msg && data -> smb_level == * p_smb_level ) {
 result = data ;
 break ;
 }
 }
 return result ;
 }