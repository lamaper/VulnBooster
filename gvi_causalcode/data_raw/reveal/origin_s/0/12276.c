static void init_lengths ( BinkContext * c , int width , int bw ) {
 width = FFALIGN ( width , 8 ) ;
 c -> bundle [ BINK_SRC_BLOCK_TYPES ] . len = av_log2 ( ( width >> 3 ) + 511 ) + 1 ;
 c -> bundle [ BINK_SRC_SUB_BLOCK_TYPES ] . len = av_log2 ( ( width >> 4 ) + 511 ) + 1 ;
 c -> bundle [ BINK_SRC_COLORS ] . len = av_log2 ( bw * 64 + 511 ) + 1 ;
 c -> bundle [ BINK_SRC_INTRA_DC ] . len = c -> bundle [ BINK_SRC_INTER_DC ] . len = c -> bundle [ BINK_SRC_X_OFF ] . len = c -> bundle [ BINK_SRC_Y_OFF ] . len = av_log2 ( ( width >> 3 ) + 511 ) + 1 ;
 c -> bundle [ BINK_SRC_PATTERN ] . len = av_log2 ( ( bw << 3 ) + 511 ) + 1 ;
 c -> bundle [ BINK_SRC_RUN ] . len = av_log2 ( bw * 48 + 511 ) + 1 ;
 }