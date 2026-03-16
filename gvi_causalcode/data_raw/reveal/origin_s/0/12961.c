static int at1_unpack_dequant ( GetBitContext * gb , AT1SUCtx * su , float spec [ AT1_SU_SAMPLES ] ) {
 int bits_used , band_num , bfu_num , i ;
 uint8_t idwls [ AT1_MAX_BFU ] ;
 uint8_t idsfs [ AT1_MAX_BFU ] ;
 su -> num_bfus = bfu_amount_tab1 [ get_bits ( gb , 3 ) ] ;
 bits_used = su -> num_bfus * 10 + 32 + bfu_amount_tab2 [ get_bits ( gb , 2 ) ] + ( bfu_amount_tab3 [ get_bits ( gb , 3 ) ] << 1 ) ;
 for ( i = 0 ;
 i < su -> num_bfus ;
 i ++ ) idwls [ i ] = get_bits ( gb , 4 ) ;
 for ( i = 0 ;
 i < su -> num_bfus ;
 i ++ ) idsfs [ i ] = get_bits ( gb , 6 ) ;
 for ( i = su -> num_bfus ;
 i < AT1_MAX_BFU ;
 i ++ ) idwls [ i ] = idsfs [ i ] = 0 ;
 for ( band_num = 0 ;
 band_num < AT1_QMF_BANDS ;
 band_num ++ ) {
 for ( bfu_num = bfu_bands_t [ band_num ] ;
 bfu_num < bfu_bands_t [ band_num + 1 ] ;
 bfu_num ++ ) {
 int pos ;
 int num_specs = specs_per_bfu [ bfu_num ] ;
 int word_len = ! ! idwls [ bfu_num ] + idwls [ bfu_num ] ;
 float scale_factor = ff_atrac_sf_table [ idsfs [ bfu_num ] ] ;
 bits_used += word_len * num_specs ;
 if ( bits_used > AT1_SU_MAX_BITS ) return AVERROR_INVALIDDATA ;
 pos = su -> log2_block_count [ band_num ] ? bfu_start_short [ bfu_num ] : bfu_start_long [ bfu_num ] ;
 if ( word_len ) {
 float max_quant = 1.0 / ( float ) ( ( 1 << ( word_len - 1 ) ) - 1 ) ;
 for ( i = 0 ;
 i < num_specs ;
 i ++ ) {
 spec [ pos + i ] = get_sbits ( gb , word_len ) * scale_factor * max_quant ;
 }
 }
 else {
 memset ( & spec [ pos ] , 0 , num_specs * sizeof ( float ) ) ;
 }
 }
 }
 return 0 ;
 }