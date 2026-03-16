int vp9_get_reference_mode_context ( const VP9_COMMON * cm , const MACROBLOCKD * xd ) {
 int ctx ;
 const MB_MODE_INFO * const above_mbmi = get_mbmi ( get_above_mi ( xd ) ) ;
 const MB_MODE_INFO * const left_mbmi = get_mbmi ( get_left_mi ( xd ) ) ;
 const int has_above = above_mbmi != NULL ;
 const int has_left = left_mbmi != NULL ;
 if ( has_above && has_left ) {
 if ( ! has_second_ref ( above_mbmi ) && ! has_second_ref ( left_mbmi ) ) ctx = ( above_mbmi -> ref_frame [ 0 ] == cm -> comp_fixed_ref ) ^ ( left_mbmi -> ref_frame [ 0 ] == cm -> comp_fixed_ref ) ;
 else if ( ! has_second_ref ( above_mbmi ) ) ctx = 2 + ( above_mbmi -> ref_frame [ 0 ] == cm -> comp_fixed_ref || ! is_inter_block ( above_mbmi ) ) ;
 else if ( ! has_second_ref ( left_mbmi ) ) ctx = 2 + ( left_mbmi -> ref_frame [ 0 ] == cm -> comp_fixed_ref || ! is_inter_block ( left_mbmi ) ) ;
 else ctx = 4 ;
 }
 else if ( has_above || has_left ) {
 const MB_MODE_INFO * edge_mbmi = has_above ? above_mbmi : left_mbmi ;
 if ( ! has_second_ref ( edge_mbmi ) ) ctx = edge_mbmi -> ref_frame [ 0 ] == cm -> comp_fixed_ref ;
 else ctx = 3 ;
 }
 else {
 ctx = 1 ;
 }
 assert ( ctx >= 0 && ctx < COMP_INTER_CONTEXTS ) ;
 return ctx ;
 }