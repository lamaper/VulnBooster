static int calculate_section_intra_ratio ( const FIRSTPASS_STATS * begin , const FIRSTPASS_STATS * end , int section_length ) {
 const FIRSTPASS_STATS * s = begin ;
 double intra_error = 0.0 ;
 double coded_error = 0.0 ;
 int i = 0 ;
 while ( s < end && i < section_length ) {
 intra_error += s -> intra_error ;
 coded_error += s -> coded_error ;
 ++ s ;
 ++ i ;
 }
 return ( int ) ( intra_error / DOUBLE_DIVIDE_CHECK ( coded_error ) ) ;
 }