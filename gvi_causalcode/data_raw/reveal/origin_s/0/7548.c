static int normalize_bits ( int num , int width ) {
 return width - av_log2 ( num ) - 1 ;
 }