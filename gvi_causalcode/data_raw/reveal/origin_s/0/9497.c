static void adapt_coef_probs ( VP9_COMMON * cm , TX_SIZE tx_size , unsigned int count_sat , unsigned int update_factor ) {
 const FRAME_CONTEXT * pre_fc = & cm -> frame_contexts [ cm -> frame_context_idx ] ;
 vp9_coeff_probs_model * const probs = cm -> fc . coef_probs [ tx_size ] ;
 const vp9_coeff_probs_model * const pre_probs = pre_fc -> coef_probs [ tx_size ] ;
 vp9_coeff_count_model * counts = cm -> counts . coef [ tx_size ] ;
 unsigned int ( * eob_counts ) [ REF_TYPES ] [ COEF_BANDS ] [ COEFF_CONTEXTS ] = cm -> counts . eob_branch [ tx_size ] ;
 int i , j , k , l , m ;
 for ( i = 0 ;
 i < PLANE_TYPES ;
 ++ i ) for ( j = 0 ;
 j < REF_TYPES ;
 ++ j ) for ( k = 0 ;
 k < COEF_BANDS ;
 ++ k ) for ( l = 0 ;
 l < BAND_COEFF_CONTEXTS ( k ) ;
 ++ l ) {
 const int n0 = counts [ i ] [ j ] [ k ] [ l ] [ ZERO_TOKEN ] ;
 const int n1 = counts [ i ] [ j ] [ k ] [ l ] [ ONE_TOKEN ] ;
 const int n2 = counts [ i ] [ j ] [ k ] [ l ] [ TWO_TOKEN ] ;
 const int neob = counts [ i ] [ j ] [ k ] [ l ] [ EOB_MODEL_TOKEN ] ;
 const unsigned int branch_ct [ UNCONSTRAINED_NODES ] [ 2 ] = {
 {
 neob , eob_counts [ i ] [ j ] [ k ] [ l ] - neob }
 , {
 n0 , n1 + n2 }
 , {
 n1 , n2 }
 }
 ;
 for ( m = 0 ;
 m < UNCONSTRAINED_NODES ;
 ++ m ) probs [ i ] [ j ] [ k ] [ l ] [ m ] = merge_probs ( pre_probs [ i ] [ j ] [ k ] [ l ] [ m ] , branch_ct [ m ] , count_sat , update_factor ) ;
 }
 }