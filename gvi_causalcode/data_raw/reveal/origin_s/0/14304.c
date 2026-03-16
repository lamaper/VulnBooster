static uint8_t vble_read_reverse_unary ( GetBitContext * gb ) {
 uint8_t val = show_bits ( gb , 8 ) ;
 if ( val ) {
 val = 7 - av_log2_16bit ( ff_reverse [ val ] ) ;
 skip_bits ( gb , val + 1 ) ;
 return val ;
 }
 else {
 skip_bits ( gb , 8 ) ;
 if ( get_bits1 ( gb ) ) return 8 ;
 }
 return UINT8_MAX ;
 }