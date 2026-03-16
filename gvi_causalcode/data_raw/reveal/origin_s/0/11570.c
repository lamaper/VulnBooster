static void arith_normalise ( ArithCoder * c ) {
 for ( ;
 ;
 ) {
 if ( c -> high >= 0x8000 ) {
 if ( c -> low < 0x8000 ) {
 if ( c -> low >= 0x4000 && c -> high < 0xC000 ) {
 c -> value -= 0x4000 ;
 c -> low -= 0x4000 ;
 c -> high -= 0x4000 ;
 }
 else {
 return ;
 }
 }
 else {
 c -> value -= 0x8000 ;
 c -> low -= 0x8000 ;
 c -> high -= 0x8000 ;
 }
 }
 c -> value <<= 1 ;
 c -> low <<= 1 ;
 c -> high <<= 1 ;
 c -> high |= 1 ;
 c -> value |= get_bits1 ( c -> gbc . gb ) ;
 }
 }