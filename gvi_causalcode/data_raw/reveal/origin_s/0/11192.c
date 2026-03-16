static struct CPMSetBindingsIn * find_binding_msg_data ( struct mswsp_ct * ct , packet_info * pinfo , void * private_data ) {
 struct CPMSetBindingsIn * result = NULL ;
 struct message_data * data = find_matching_request_by_fid ( ct , pinfo , 0xD0 , TRUE , private_data ) ;
 if ( data ) {
 result = & data -> content . bindingsin ;
 }
 return result ;
 }