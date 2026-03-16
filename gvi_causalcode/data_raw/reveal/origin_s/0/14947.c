static rtp_dyn_payload_t * rtp_dyn_payload_ref ( rtp_dyn_payload_t * rtp_dyn_payload ) {
 if ( rtp_dyn_payload ) {
 rtp_dyn_payload -> ref_count ++ ;
 }
 return rtp_dyn_payload ;
 }