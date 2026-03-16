static gboolean is_64bit_mode ( struct mswsp_ct * ct , packet_info * pinfo , gboolean * result , void * private_data ) {
 guint32 client_ver = 0 ;
 guint32 server_ver = 0 ;
 struct message_data * data = find_matching_request_by_fid ( ct , pinfo , 0xC8 , TRUE , private_data ) ;
 if ( data ) {
 client_ver = data -> content . version ;
 data = find_matching_request_by_fid ( ct , pinfo , 0xC8 , FALSE , private_data ) ;
 if ( data ) {
 server_ver = data -> content . version ;
 * result = ( server_ver & 0xffff0000 ) && ( client_ver & 0xffff0000 ) ;
 return TRUE ;
 }
 }
 return FALSE ;
 }