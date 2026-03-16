static void lsf_decode_fp ( float * lsfnew , float * lsf_history , const SiprParameters * parm ) {
 int i ;
 float lsf_tmp [ LP_FILTER_ORDER ] ;
 dequant ( lsf_tmp , parm -> vq_indexes , lsf_codebooks ) ;
 for ( i = 0 ;
 i < LP_FILTER_ORDER ;
 i ++ ) lsfnew [ i ] = lsf_history [ i ] * 0.33 + lsf_tmp [ i ] + mean_lsf [ i ] ;
 ff_sort_nearly_sorted_floats ( lsfnew , LP_FILTER_ORDER - 1 ) ;
 ff_set_min_dist_lsf ( lsfnew , LSFQ_DIFF_MIN , LP_FILTER_ORDER - 1 ) ;
 lsfnew [ 9 ] = FFMIN ( lsfnew [ LP_FILTER_ORDER - 1 ] , 1.3 * M_PI ) ;
 memcpy ( lsf_history , lsf_tmp , LP_FILTER_ORDER * sizeof ( * lsf_history ) ) ;
 for ( i = 0 ;
 i < LP_FILTER_ORDER - 1 ;
 i ++ ) lsfnew [ i ] = cos ( lsfnew [ i ] ) ;
 lsfnew [ LP_FILTER_ORDER - 1 ] *= 6.153848 / M_PI ;
 }