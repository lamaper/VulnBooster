static int at1_imdct_block ( AT1SUCtx * su , AT1Ctx * q ) {
 int band_num , band_samples , log2_block_count , nbits , num_blocks , block_size ;
 unsigned int start_pos , ref_pos = 0 , pos = 0 ;
 for ( band_num = 0 ;
 band_num < AT1_QMF_BANDS ;
 band_num ++ ) {
 float * prev_buf ;
 int j ;
 band_samples = samples_per_band [ band_num ] ;
 log2_block_count = su -> log2_block_count [ band_num ] ;
 num_blocks = 1 << log2_block_count ;
 if ( num_blocks == 1 ) {
 block_size = band_samples >> log2_block_count ;
 nbits = mdct_long_nbits [ band_num ] - log2_block_count ;
 if ( nbits != 5 && nbits != 7 && nbits != 8 ) return AVERROR_INVALIDDATA ;
 }
 else {
 block_size = 32 ;
 nbits = 5 ;
 }
 start_pos = 0 ;
 prev_buf = & su -> spectrum [ 1 ] [ ref_pos + band_samples - 16 ] ;
 for ( j = 0 ;
 j < num_blocks ;
 j ++ ) {
 at1_imdct ( q , & q -> spec [ pos ] , & su -> spectrum [ 0 ] [ ref_pos + start_pos ] , nbits , band_num ) ;
 q -> fdsp . vector_fmul_window ( & q -> bands [ band_num ] [ start_pos ] , prev_buf , & su -> spectrum [ 0 ] [ ref_pos + start_pos ] , ff_sine_32 , 16 ) ;
 prev_buf = & su -> spectrum [ 0 ] [ ref_pos + start_pos + 16 ] ;
 start_pos += block_size ;
 pos += block_size ;
 }
 if ( num_blocks == 1 ) memcpy ( q -> bands [ band_num ] + 32 , & su -> spectrum [ 0 ] [ ref_pos + 16 ] , 240 * sizeof ( float ) ) ;
 ref_pos += band_samples ;
 }
 FFSWAP ( float * , su -> spectrum [ 0 ] , su -> spectrum [ 1 ] ) ;
 return 0 ;
 }