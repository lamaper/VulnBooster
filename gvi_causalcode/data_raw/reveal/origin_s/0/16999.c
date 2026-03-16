static void dissect_q931_date_time_ie ( tvbuff_t * tvb , packet_info * pinfo , int offset , int len , proto_tree * tree ) {
 if ( len == 6 ) {
 proto_tree_add_bytes_format_value ( tree , hf_q931_date_time , tvb , offset , 6 , NULL , "%02u-%02u-%02u %02u:%02u:%02u" , tvb_get_guint8 ( tvb , offset + 0 ) , tvb_get_guint8 ( tvb , offset + 1 ) , tvb_get_guint8 ( tvb , offset + 2 ) , tvb_get_guint8 ( tvb , offset + 3 ) , tvb_get_guint8 ( tvb , offset + 4 ) , tvb_get_guint8 ( tvb , offset + 5 ) ) ;
 }
 else if ( len == 5 ) {
 proto_tree_add_bytes_format_value ( tree , hf_q931_date_time , tvb , offset , 5 , NULL , "%02u-%02u-%02u %02u:%02u:00" , tvb_get_guint8 ( tvb , offset + 0 ) , tvb_get_guint8 ( tvb , offset + 1 ) , tvb_get_guint8 ( tvb , offset + 2 ) , tvb_get_guint8 ( tvb , offset + 3 ) , tvb_get_guint8 ( tvb , offset + 4 ) ) ;
 }
 else {
 proto_tree_add_expert_format ( tree , pinfo , & ei_q931_date_time , tvb , offset , len , "Date/time: length is %d, should be 5 or 6" , len ) ;
 }
 }