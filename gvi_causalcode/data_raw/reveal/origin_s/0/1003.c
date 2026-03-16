static int dissect_AllJoyn_ardp ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , void * data _U_ ) {
 alljoyn_ardp_tree_data tree_data = {
 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 }
 ;
 gint packet_length = tvb_reported_length ( tvb ) ;
 proto_item * alljoyn_item = NULL ;
 gboolean fragmentedPacket = FALSE ;
 if ( protocol_is_alljoyn_message ( tvb , 0 , FALSE ) ) {
 return dissect_AllJoyn_message ( tvb , pinfo , tree , 0 ) ;
 }
 if ( ! protocol_is_ardp ( tvb ) ) {
 return 0 ;
 }
 pinfo -> desegment_len = 0 ;
 alljoyn_item = proto_tree_add_item ( tree , proto_AllJoyn_ardp , tvb , 0 , - 1 , ENC_NA ) ;
 tree_data . alljoyn_tree = proto_item_add_subtree ( alljoyn_item , ett_alljoyn_ardp ) ;
 ardp_parse_header ( tvb , pinfo , & tree_data ) ;
 if ( pinfo -> desegment_len != 0 ) {
 return tree_data . offset ;
 }
 if ( tree_data . offset != 0 ) {
 col_set_str ( pinfo -> cinfo , COL_PROTOCOL , "ALLJOYN-ARDP" ) ;
 }
 if ( tree_data . offset < packet_length ) {
 gint return_value = 0 ;
 if ( protocol_is_alljoyn_message ( tvb , tree_data . offset , TRUE ) ) {
 return_value = dissect_AllJoyn_message ( tvb , pinfo , tree , tree_data . offset ) ;
 }
 else {
 fragmentedPacket = ! tree_data . syn && ( tree_data . sequence > tree_data . start_sequence ) ;
 }
 if ( return_value > tree_data . offset ) {
 return return_value ;
 }
 }
 col_clear ( pinfo -> cinfo , COL_INFO ) ;
 col_append_str ( pinfo -> cinfo , COL_INFO , "flags:" ) ;
 if ( tree_data . syn ) {
 col_append_str ( pinfo -> cinfo , COL_INFO , " SYN" ) ;
 }
 if ( tree_data . ack ) {
 col_append_str ( pinfo -> cinfo , COL_INFO , " ACK" ) ;
 }
 if ( tree_data . eak ) {
 col_append_str ( pinfo -> cinfo , COL_INFO , " EAK" ) ;
 }
 if ( tree_data . rst ) {
 col_append_str ( pinfo -> cinfo , COL_INFO , " RST" ) ;
 }
 if ( tree_data . nul ) {
 col_append_str ( pinfo -> cinfo , COL_INFO , " NUL" ) ;
 }
 col_append_fstr ( pinfo -> cinfo , COL_INFO , " SEQ: %10u" , tree_data . sequence ) ;
 col_append_fstr ( pinfo -> cinfo , COL_INFO , " ACK: %10u" , tree_data . acknowledge ) ;
 if ( fragmentedPacket ) {
 guint fragment = ( tree_data . sequence - tree_data . start_sequence ) + 1 ;
 col_append_sep_fstr ( pinfo -> cinfo , COL_INFO , NULL , "Fragment %d of %d for a previous ALLJOYN message" , fragment , tree_data . fragment_count ) ;
 }
 return tree_data . offset ;
 }