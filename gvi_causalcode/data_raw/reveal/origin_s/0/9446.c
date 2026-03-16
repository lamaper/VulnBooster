static inline int get_bits_diff ( MpegEncContext * s ) {
 const int bits = put_bits_count ( & s -> pb ) ;
 const int last = s -> last_bits ;
 s -> last_bits = bits ;
 return bits - last ;
 }