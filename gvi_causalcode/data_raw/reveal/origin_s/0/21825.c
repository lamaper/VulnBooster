static int frame_max_bits ( const RATE_CONTROL * rc , const VP9EncoderConfig * oxcf ) {
 int64_t max_bits = ( ( int64_t ) rc -> avg_frame_bandwidth * ( int64_t ) oxcf -> two_pass_vbrmax_section ) / 100 ;
 if ( max_bits < 0 ) max_bits = 0 ;
 else if ( max_bits > rc -> max_frame_bandwidth ) max_bits = rc -> max_frame_bandwidth ;
 return ( int ) max_bits ;
 }