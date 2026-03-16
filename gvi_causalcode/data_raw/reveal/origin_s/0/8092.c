static int dca_parse_audio_coding_header ( DCAContext * s , int base_channel ) {
 int i , j ;
 static const float adj_table [ 4 ] = {
 1.0 , 1.1250 , 1.2500 , 1.4375 }
 ;
 static const int bitlen [ 11 ] = {
 0 , 1 , 2 , 2 , 2 , 2 , 3 , 3 , 3 , 3 , 3 }
 ;
 static const int thr [ 11 ] = {
 0 , 1 , 3 , 3 , 3 , 3 , 7 , 7 , 7 , 7 , 7 }
 ;
 s -> total_channels = get_bits ( & s -> gb , 3 ) + 1 + base_channel ;
 s -> prim_channels = s -> total_channels ;
 if ( s -> prim_channels > DCA_PRIM_CHANNELS_MAX ) s -> prim_channels = DCA_PRIM_CHANNELS_MAX ;
 for ( i = base_channel ;
 i < s -> prim_channels ;
 i ++ ) {
 s -> subband_activity [ i ] = get_bits ( & s -> gb , 5 ) + 2 ;
 if ( s -> subband_activity [ i ] > DCA_SUBBANDS ) s -> subband_activity [ i ] = DCA_SUBBANDS ;
 }
 for ( i = base_channel ;
 i < s -> prim_channels ;
 i ++ ) {
 s -> vq_start_subband [ i ] = get_bits ( & s -> gb , 5 ) + 1 ;
 if ( s -> vq_start_subband [ i ] > DCA_SUBBANDS ) s -> vq_start_subband [ i ] = DCA_SUBBANDS ;
 }
 get_array ( & s -> gb , s -> joint_intensity + base_channel , s -> prim_channels - base_channel , 3 ) ;
 get_array ( & s -> gb , s -> transient_huffman + base_channel , s -> prim_channels - base_channel , 2 ) ;
 get_array ( & s -> gb , s -> scalefactor_huffman + base_channel , s -> prim_channels - base_channel , 3 ) ;
 get_array ( & s -> gb , s -> bitalloc_huffman + base_channel , s -> prim_channels - base_channel , 3 ) ;
 if ( ! base_channel ) memset ( s -> quant_index_huffman , 0 , sizeof ( s -> quant_index_huffman ) ) ;
 for ( j = 1 ;
 j < 11 ;
 j ++ ) for ( i = base_channel ;
 i < s -> prim_channels ;
 i ++ ) s -> quant_index_huffman [ i ] [ j ] = get_bits ( & s -> gb , bitlen [ j ] ) ;
 for ( j = 0 ;
 j < 11 ;
 j ++ ) for ( i = base_channel ;
 i < s -> prim_channels ;
 i ++ ) s -> scalefactor_adj [ i ] [ j ] = 1 ;
 for ( j = 1 ;
 j < 11 ;
 j ++ ) for ( i = base_channel ;
 i < s -> prim_channels ;
 i ++ ) if ( s -> quant_index_huffman [ i ] [ j ] < thr [ j ] ) s -> scalefactor_adj [ i ] [ j ] = adj_table [ get_bits ( & s -> gb , 2 ) ] ;
 if ( s -> crc_present ) {
 get_bits ( & s -> gb , 16 ) ;
 }
 s -> current_subframe = 0 ;
 s -> current_subsubframe = 0 ;

 av_log ( s -> avctx , AV_LOG_DEBUG , "prim channels: %i\n" , s -> prim_channels ) ;
 for ( i = base_channel ;
 i < s -> prim_channels ;
 i ++ ) {
 av_log ( s -> avctx , AV_LOG_DEBUG , "subband activity: %i\n" , s -> subband_activity [ i ] ) ;
 av_log ( s -> avctx , AV_LOG_DEBUG , "vq start subband: %i\n" , s -> vq_start_subband [ i ] ) ;
 av_log ( s -> avctx , AV_LOG_DEBUG , "joint intensity: %i\n" , s -> joint_intensity [ i ] ) ;
 av_log ( s -> avctx , AV_LOG_DEBUG , "transient mode codebook: %i\n" , s -> transient_huffman [ i ] ) ;
 av_log ( s -> avctx , AV_LOG_DEBUG , "scale factor codebook: %i\n" , s -> scalefactor_huffman [ i ] ) ;
 av_log ( s -> avctx , AV_LOG_DEBUG , "bit allocation quantizer: %i\n" , s -> bitalloc_huffman [ i ] ) ;
 av_log ( s -> avctx , AV_LOG_DEBUG , "quant index huff:" ) ;
 for ( j = 0 ;
 j < 11 ;
 j ++ ) av_log ( s -> avctx , AV_LOG_DEBUG , " %i" , s -> quant_index_huffman [ i ] [ j ] ) ;
 av_log ( s -> avctx , AV_LOG_DEBUG , "\n" ) ;
 av_log ( s -> avctx , AV_LOG_DEBUG , "scalefac adj:" ) ;
 for ( j = 0 ;
 j < 11 ;
 j ++ ) av_log ( s -> avctx , AV_LOG_DEBUG , " %1.3f" , s -> scalefactor_adj [ i ] [ j ] ) ;
 av_log ( s -> avctx , AV_LOG_DEBUG , "\n" ) ;
 }

 }