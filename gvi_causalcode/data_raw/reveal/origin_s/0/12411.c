static void dissect_q931_e2e_transit_delay_ie ( tvbuff_t * tvb , packet_info * pinfo , int offset , int len , proto_tree * tree , proto_item * item ) {
 int value_len ;
 if ( len == 0 ) return ;
 value_len = dissect_q931_guint16_value ( tvb , pinfo , offset , len , tree , item , hf_q931_cumulative_transit_delay ) ;
 if ( value_len < 0 ) return ;
 offset += value_len ;
 len -= value_len ;
 if ( len == 0 ) return ;
 value_len = dissect_q931_guint16_value ( tvb , pinfo , offset , len , tree , item , hf_q931_requested_end_to_end_transit_delay ) ;
 if ( value_len < 0 ) return ;
 offset += value_len ;
 len -= value_len ;
 if ( len == 0 ) return ;
 dissect_q931_guint16_value ( tvb , pinfo , offset , len , tree , item , hf_q931_maximum_end_to_end_transit_delay ) ;
 }