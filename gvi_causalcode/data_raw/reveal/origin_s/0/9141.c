static int at1_parse_bsm ( GetBitContext * gb , int log2_block_cnt [ AT1_QMF_BANDS ] ) {
 int log2_block_count_tmp , i ;
 for ( i = 0 ;
 i < 2 ;
 i ++ ) {
 log2_block_count_tmp = get_bits ( gb , 2 ) ;
 if ( log2_block_count_tmp & 1 ) return AVERROR_INVALIDDATA ;
 log2_block_cnt [ i ] = 2 - log2_block_count_tmp ;
 }
 log2_block_count_tmp = get_bits ( gb , 2 ) ;
 if ( log2_block_count_tmp != 0 && log2_block_count_tmp != 3 ) return AVERROR_INVALIDDATA ;
 log2_block_cnt [ IDX_HIGH_BAND ] = 3 - log2_block_count_tmp ;
 skip_bits ( gb , 2 ) ;
 return 0 ;
 }