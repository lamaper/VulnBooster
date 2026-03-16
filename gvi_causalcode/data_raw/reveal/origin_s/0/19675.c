static iax_packet_data * iax_new_packet_data ( iax_call_data * call , gboolean reversed ) {
 iax_packet_data * p = wmem_new ( wmem_file_scope ( ) , iax_packet_data ) ;
 p -> first_time = TRUE ;
 p -> call_data = call ;
 p -> codec = 0 ;
 p -> reversed = reversed ;
 p -> abstime . secs = - 1 ;
 p -> abstime . nsecs = - 1 ;
 return p ;
 }