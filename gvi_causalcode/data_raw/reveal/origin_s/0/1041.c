static struct rows_data * find_rowsin_msg_data ( struct mswsp_ct * ct , packet_info * pinfo , void * private_data ) {
 struct rows_data * result = NULL ;
 struct message_data * data = find_matching_request_by_fid ( ct , pinfo , 0xCC , TRUE , private_data ) ;
 if ( data ) {
 result = & data -> content . rowsin ;
 }
 return result ;
 }