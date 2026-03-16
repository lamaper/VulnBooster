static void arith_init ( ArithCoder * c , GetBitContext * gb ) {
 c -> low = 0 ;
 c -> high = 0xFFFF ;
 c -> value = get_bits ( gb , 16 ) ;
 c -> gbc . gb = gb ;
 c -> get_model_sym = arith_get_model_sym ;
 c -> get_number = arith_get_number ;
 }