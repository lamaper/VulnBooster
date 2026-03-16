static void build_tree_distribution ( VP9_COMP * cpi , TX_SIZE tx_size , vp9_coeff_stats * coef_branch_ct , vp9_coeff_probs_model * coef_probs ) {
 vp9_coeff_count * coef_counts = cpi -> coef_counts [ tx_size ] ;
 unsigned int ( * eob_branch_ct ) [ REF_TYPES ] [ COEF_BANDS ] [ COEFF_CONTEXTS ] = cpi -> common . counts . eob_branch [ tx_size ] ;
 int i , j , k , l , m ;
 for ( i = 0 ;
 i < PLANE_TYPES ;
 ++ i ) {
 for ( j = 0 ;
 j < REF_TYPES ;
 ++ j ) {
 for ( k = 0 ;
 k < COEF_BANDS ;
 ++ k ) {
 for ( l = 0 ;
 l < BAND_COEFF_CONTEXTS ( k ) ;
 ++ l ) {
 vp9_tree_probs_from_distribution ( vp9_coef_tree , coef_branch_ct [ i ] [ j ] [ k ] [ l ] , coef_counts [ i ] [ j ] [ k ] [ l ] ) ;
 coef_branch_ct [ i ] [ j ] [ k ] [ l ] [ 0 ] [ 1 ] = eob_branch_ct [ i ] [ j ] [ k ] [ l ] - coef_branch_ct [ i ] [ j ] [ k ] [ l ] [ 0 ] [ 0 ] ;
 for ( m = 0 ;
 m < UNCONSTRAINED_NODES ;
 ++ m ) coef_probs [ i ] [ j ] [ k ] [ l ] [ m ] = get_binary_prob ( coef_branch_ct [ i ] [ j ] [ k ] [ l ] [ m ] [ 0 ] , coef_branch_ct [ i ] [ j ] [ k ] [ l ] [ m ] [ 1 ] ) ;
 }
 }
 }
 }
 }