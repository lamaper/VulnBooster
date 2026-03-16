int call_ber_oid_callback ( const char * oid , tvbuff_t * tvb , int offset , packet_info * pinfo , proto_tree * tree , void * data ) {
 tvbuff_t * next_tvb ;
 const char * syntax = NULL ;
 int len = 0 ;
 if ( ! tvb ) {
 return offset ;
 }
 next_tvb = tvb_new_subset_remaining ( tvb , offset ) ;
 if ( oid == NULL || ( ( ( ( syntax = get_ber_oid_syntax ( oid ) ) == NULL ) || ( len = dissector_try_string ( ber_syntax_dissector_table , syntax , next_tvb , pinfo , tree , data ) ) == 0 ) && ( len = dissector_try_string ( ber_oid_dissector_table , oid , next_tvb , pinfo , tree , data ) ) == 0 ) ) {
 proto_item * item = NULL ;
 proto_tree * next_tree = NULL ;
 gint length_remaining ;
 length_remaining = tvb_reported_length_remaining ( tvb , offset ) ;
 if ( oid == NULL ) {
 item = proto_tree_add_expert ( tree , pinfo , & ei_ber_no_oid , next_tvb , 0 , length_remaining ) ;
 }
 else if ( tvb_get_ntohs ( tvb , offset ) != 0x0500 ) {
 if ( syntax ) {
 item = proto_tree_add_expert_format ( tree , pinfo , & ei_ber_syntax_not_implemented , next_tvb , 0 , length_remaining , "BER: Dissector for syntax:%s not implemented." " Contact Wireshark developers if you want this supported" , syntax ) ;
 }
 else {
 item = proto_tree_add_expert ( tree , pinfo , & ei_ber_oid_not_implemented , next_tvb , 0 , length_remaining ) ;
 }
 }
 else {
 next_tree = tree ;
 }
 if ( decode_unexpected ) {
 int ber_offset ;
 gint32 ber_len ;
 if ( item ) {
 next_tree = proto_item_add_subtree ( item , ett_ber_unknown ) ;
 }
 ber_offset = get_ber_identifier ( next_tvb , 0 , NULL , NULL , NULL ) ;
 ber_offset = get_ber_length ( next_tvb , ber_offset , & ber_len , NULL ) ;
 if ( ( ber_len + ber_offset ) == length_remaining ) {
 dissect_unknown_ber ( pinfo , next_tvb , 0 , next_tree ) ;
 }
 else {
 proto_tree_add_item ( next_tree , hf_ber_unknown_data , next_tvb , 0 , length_remaining , ENC_NA ) ;
 }
 }
 len = length_remaining ;
 }
 offset += len ;
 return offset ;
 }