static int sbr_make_f_derived ( AACContext * ac , SpectralBandReplication * sbr ) {
 int k , temp ;
 sbr -> n [ 1 ] = sbr -> n_master - sbr -> spectrum_params . bs_xover_band ;
 sbr -> n [ 0 ] = ( sbr -> n [ 1 ] + 1 ) >> 1 ;
 memcpy ( sbr -> f_tablehigh , & sbr -> f_master [ sbr -> spectrum_params . bs_xover_band ] , ( sbr -> n [ 1 ] + 1 ) * sizeof ( sbr -> f_master [ 0 ] ) ) ;
 sbr -> m [ 1 ] = sbr -> f_tablehigh [ sbr -> n [ 1 ] ] - sbr -> f_tablehigh [ 0 ] ;
 sbr -> kx [ 1 ] = sbr -> f_tablehigh [ 0 ] ;
 if ( sbr -> kx [ 1 ] + sbr -> m [ 1 ] > 64 ) {
 av_log ( ac -> avctx , AV_LOG_ERROR , "Stop frequency border too high: %d\n" , sbr -> kx [ 1 ] + sbr -> m [ 1 ] ) ;
 return - 1 ;
 }
 if ( sbr -> kx [ 1 ] > 32 ) {
 av_log ( ac -> avctx , AV_LOG_ERROR , "Start frequency border too high: %d\n" , sbr -> kx [ 1 ] ) ;
 return - 1 ;
 }
 sbr -> f_tablelow [ 0 ] = sbr -> f_tablehigh [ 0 ] ;
 temp = sbr -> n [ 1 ] & 1 ;
 for ( k = 1 ;
 k <= sbr -> n [ 0 ] ;
 k ++ ) sbr -> f_tablelow [ k ] = sbr -> f_tablehigh [ 2 * k - temp ] ;
 sbr -> n_q = FFMAX ( 1 , lrintf ( sbr -> spectrum_params . bs_noise_bands * log2f ( sbr -> k [ 2 ] / ( float ) sbr -> kx [ 1 ] ) ) ) ;
 if ( sbr -> n_q > 5 ) {
 av_log ( ac -> avctx , AV_LOG_ERROR , "Too many noise floor scale factors: %d\n" , sbr -> n_q ) ;
 return - 1 ;
 }
 sbr -> f_tablenoise [ 0 ] = sbr -> f_tablelow [ 0 ] ;
 temp = 0 ;
 for ( k = 1 ;
 k <= sbr -> n_q ;
 k ++ ) {
 temp += ( sbr -> n [ 0 ] - temp ) / ( sbr -> n_q + 1 - k ) ;
 sbr -> f_tablenoise [ k ] = sbr -> f_tablelow [ temp ] ;
 }
 if ( sbr_hf_calc_npatches ( ac , sbr ) < 0 ) return - 1 ;
 sbr_make_f_tablelim ( sbr ) ;
 sbr -> data [ 0 ] . f_indexnoise = 0 ;
 sbr -> data [ 1 ] . f_indexnoise = 0 ;
 return 0 ;
 }