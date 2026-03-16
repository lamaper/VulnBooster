int vp9_get_pred_context_switchable_interp ( const MACROBLOCKD * xd ) {
 const MB_MODE_INFO * const left_mbmi = get_mbmi ( get_left_mi ( xd ) ) ;
 const int left_type = left_mbmi != NULL && is_inter_block ( left_mbmi ) ? left_mbmi -> interp_filter : SWITCHABLE_FILTERS ;
 const MB_MODE_INFO * const above_mbmi = get_mbmi ( get_above_mi ( xd ) ) ;
 const int above_type = above_mbmi != NULL && is_inter_block ( above_mbmi ) ? above_mbmi -> interp_filter : SWITCHABLE_FILTERS ;
 if ( left_type == above_type ) return left_type ;
 else if ( left_type == SWITCHABLE_FILTERS && above_type != SWITCHABLE_FILTERS ) return above_type ;
 else if ( left_type != SWITCHABLE_FILTERS && above_type == SWITCHABLE_FILTERS ) return left_type ;
 else return SWITCHABLE_FILTERS ;
 }