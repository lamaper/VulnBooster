static qcelp_packet_rate buf_size2bitrate ( const int buf_size ) {
 switch ( buf_size ) {
 case 35 : return RATE_FULL ;
 case 17 : return RATE_HALF ;
 case 8 : return RATE_QUARTER ;
 case 4 : return RATE_OCTAVE ;
 case 1 : return SILENCE ;
 }
 return I_F_Q ;
 }