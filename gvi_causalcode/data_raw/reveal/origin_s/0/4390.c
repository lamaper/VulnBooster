int vp9_get_intra_inter_context ( const MACROBLOCKD * xd ) {
 const MB_MODE_INFO * const above_mbmi = get_mbmi ( get_above_mi ( xd ) ) ;
 const MB_MODE_INFO * const left_mbmi = get_mbmi ( get_left_mi ( xd ) ) ;
 const int has_above = above_mbmi != NULL ;
 const int has_left = left_mbmi != NULL ;
 if ( has_above && has_left ) {
 const int above_intra = ! is_inter_block ( above_mbmi ) ;
 const int left_intra = ! is_inter_block ( left_mbmi ) ;
 return left_intra && above_intra ? 3 : left_intra || above_intra ;
 }
 else if ( has_above || has_left ) {
 return 2 * ! is_inter_block ( has_above ? above_mbmi : left_mbmi ) ;
 }
 else {
 return 0 ;
 }
 }