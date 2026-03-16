static void at1_imdct ( AT1Ctx * q , float * spec , float * out , int nbits , int rev_spec ) {
 FFTContext * mdct_context = & q -> mdct_ctx [ nbits - 5 - ( nbits > 6 ) ] ;
 int transf_size = 1 << nbits ;
 if ( rev_spec ) {
 int i ;
 for ( i = 0 ;
 i < transf_size / 2 ;
 i ++ ) FFSWAP ( float , spec [ i ] , spec [ transf_size - 1 - i ] ) ;
 }
 mdct_context -> imdct_half ( mdct_context , out , spec ) ;
 }