static proto_item * ber_add_bad_length_error ( packet_info * pinfo , proto_tree * tree , const char * name , tvbuff_t * tvb , const gint start , gint length ) {
 proto_item * ti ;
 ti = proto_tree_add_string_format ( tree , hf_ber_error , tvb , start , length , "illegal_length" , "%s: length of item (%d) is not valid" , name , length ) ;
 expert_add_info_format ( pinfo , ti , & ei_ber_error_length , "Length of item (%d) is not valid" , length ) ;
 return ti ;
 }