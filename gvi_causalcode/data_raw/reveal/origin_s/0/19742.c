static void init_quant_matrix ( VC2EncContext * s ) {
 int level , orientation ;
 if ( s -> wavelet_depth <= 4 && s -> quant_matrix == VC2_QM_DEF ) {
 s -> custom_quant_matrix = 0 ;
 for ( level = 0 ;
 level < s -> wavelet_depth ;
 level ++ ) {
 s -> quant [ level ] [ 0 ] = ff_dirac_default_qmat [ s -> wavelet_idx ] [ level ] [ 0 ] ;
 s -> quant [ level ] [ 1 ] = ff_dirac_default_qmat [ s -> wavelet_idx ] [ level ] [ 1 ] ;
 s -> quant [ level ] [ 2 ] = ff_dirac_default_qmat [ s -> wavelet_idx ] [ level ] [ 2 ] ;
 s -> quant [ level ] [ 3 ] = ff_dirac_default_qmat [ s -> wavelet_idx ] [ level ] [ 3 ] ;
 }
 return ;
 }
 s -> custom_quant_matrix = 1 ;
 if ( s -> quant_matrix == VC2_QM_DEF ) {
 for ( level = 0 ;
 level < s -> wavelet_depth ;
 level ++ ) {
 for ( orientation = 0 ;
 orientation < 4 ;
 orientation ++ ) {
 if ( level <= 3 ) s -> quant [ level ] [ orientation ] = ff_dirac_default_qmat [ s -> wavelet_idx ] [ level ] [ orientation ] ;
 else s -> quant [ level ] [ orientation ] = vc2_qm_col_tab [ level ] [ orientation ] ;
 }
 }
 }
 else if ( s -> quant_matrix == VC2_QM_COL ) {
 for ( level = 0 ;
 level < s -> wavelet_depth ;
 level ++ ) {
 for ( orientation = 0 ;
 orientation < 4 ;
 orientation ++ ) {
 s -> quant [ level ] [ orientation ] = vc2_qm_col_tab [ level ] [ orientation ] ;
 }
 }
 }
 else {
 for ( level = 0 ;
 level < s -> wavelet_depth ;
 level ++ ) {
 for ( orientation = 0 ;
 orientation < 4 ;
 orientation ++ ) {
 s -> quant [ level ] [ orientation ] = vc2_qm_flat_tab [ level ] [ orientation ] ;
 }
 }
 }
 }