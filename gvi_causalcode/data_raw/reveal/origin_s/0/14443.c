static gint dissect_AllJoyn_message ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , gint offset ) {
 proto_item * message_item ;
 proto_tree * message_tree ;
 gint last_offset = - 1 ;
 gint packet_length ;
 gboolean is_ardp = FALSE ;
 if ( offset != 0 ) {
 is_ardp = TRUE ;
 }
 pinfo -> desegment_len = 0 ;
 packet_length = tvb_reported_length ( tvb ) ;
 col_clear ( pinfo -> cinfo , COL_INFO ) ;
 col_set_str ( pinfo -> cinfo , COL_PROTOCOL , "ALLJOYN" ) ;
 message_item = proto_tree_add_item ( tree , proto_AllJoyn_mess , tvb , offset , - 1 , ENC_NA ) ;
 message_tree = proto_item_add_subtree ( message_item , ett_alljoyn_mess ) ;
 while ( offset < packet_length && offset > last_offset ) {
 last_offset = offset ;
 if ( ! is_ardp ) {
 offset = handle_message_connect ( tvb , pinfo , offset , message_tree ) ;
 if ( offset >= packet_length ) {
 break ;
 }
 offset = handle_message_sasl ( tvb , pinfo , offset , message_tree ) ;
 if ( offset >= packet_length ) {
 break ;
 }
 }
 offset = handle_message_header_body ( tvb , pinfo , offset , message_tree , is_ardp ) ;
 }
 return offset ;
 }