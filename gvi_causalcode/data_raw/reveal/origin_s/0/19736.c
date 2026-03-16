static int get_skip_encode_frame ( const VP9_COMMON * cm ) {
 unsigned int intra_count = 0 , inter_count = 0 ;
 int j ;
 for ( j = 0 ;
 j < INTRA_INTER_CONTEXTS ;
 ++ j ) {
 intra_count += cm -> counts . intra_inter [ j ] [ 0 ] ;
 inter_count += cm -> counts . intra_inter [ j ] [ 1 ] ;
 }
 return ( intra_count << 2 ) < inter_count && cm -> frame_type != KEY_FRAME && cm -> show_frame ;
 }