static int remaining_bits ( WmallDecodeCtx * s , GetBitContext * gb ) {
 return s -> buf_bit_size - get_bits_count ( gb ) ;
 }