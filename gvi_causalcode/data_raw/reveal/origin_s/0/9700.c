static void fill_noise_buffer ( MLPDecodeContext * m , unsigned int substr ) {
 SubStream * s = & m -> substream [ substr ] ;
 unsigned int i ;
 uint32_t seed = s -> noisegen_seed ;
 for ( i = 0 ;
 i < m -> access_unit_size_pow2 ;
 i ++ ) {
 uint8_t seed_shr15 = seed >> 15 ;
 m -> noise_buffer [ i ] = noise_table [ seed_shr15 ] ;
 seed = ( seed << 8 ) ^ seed_shr15 ^ ( seed_shr15 << 5 ) ;
 }
 s -> noisegen_seed = seed ;
 }