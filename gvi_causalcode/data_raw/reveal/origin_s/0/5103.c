static int call_ber_syntax_callback ( const char * syntax , tvbuff_t * tvb , int offset , packet_info * pinfo , proto_tree * tree ) {
 tvbuff_t * next_tvb ;
 int len = 0 ;
 next_tvb = tvb_new_subset_remaining ( tvb , offset ) ;
 if ( syntax == NULL || ( len = dissector_try_string ( ber_syntax_dissector_table , syntax , next_tvb , pinfo , tree , NULL ) ) == 0 ) {
 proto_item * item = NULL ;
 if ( syntax == NULL ) {
 item = proto_tree_add_expert_format ( tree , pinfo , & ei_ber_no_oid , next_tvb , 0 , tvb_reported_length_remaining ( tvb , offset ) , "BER: No syntax supplied to call_ber_syntax_callback" ) ;
 }
 else {
 item = proto_tree_add_expert_format ( tree , pinfo , & ei_ber_syntax_not_implemented , next_tvb , 0 , tvb_reported_length_remaining ( tvb , offset ) , "BER: Dissector for syntax:%s not implemented." " Contact Wireshark developers if you want this supported" , syntax ) ;
 }
 if ( decode_unexpected ) {
 proto_tree * unknown_tree = proto_item_add_subtree ( item , ett_ber_unknown ) ;
 dissect_unknown_ber ( pinfo , next_tvb , 0 , unknown_tree ) ;
 }
 len = tvb_reported_length_remaining ( tvb , offset ) ;
 }
 offset += len ;
 return offset ;
 }