int vp9_get_pred_context_comp_ref_p ( const VP9_COMMON * cm , const MACROBLOCKD * xd ) {
 int pred_context ;
 const MB_MODE_INFO * const above_mbmi = get_mbmi ( get_above_mi ( xd ) ) ;
 const MB_MODE_INFO * const left_mbmi = get_mbmi ( get_left_mi ( xd ) ) ;
 const int above_in_image = above_mbmi != NULL ;
 const int left_in_image = left_mbmi != NULL ;
 const int fix_ref_idx = cm -> ref_frame_sign_bias [ cm -> comp_fixed_ref ] ;
 const int var_ref_idx = ! fix_ref_idx ;
 if ( above_in_image && left_in_image ) {
 const int above_intra = ! is_inter_block ( above_mbmi ) ;
 const int left_intra = ! is_inter_block ( left_mbmi ) ;
 if ( above_intra && left_intra ) {
 pred_context = 2 ;
 }
 else if ( above_intra || left_intra ) {
 const MB_MODE_INFO * edge_mbmi = above_intra ? left_mbmi : above_mbmi ;
 if ( ! has_second_ref ( edge_mbmi ) ) pred_context = 1 + 2 * ( edge_mbmi -> ref_frame [ 0 ] != cm -> comp_var_ref [ 1 ] ) ;
 else pred_context = 1 + 2 * ( edge_mbmi -> ref_frame [ var_ref_idx ] != cm -> comp_var_ref [ 1 ] ) ;
 }
 else {
 const int l_sg = ! has_second_ref ( left_mbmi ) ;
 const int a_sg = ! has_second_ref ( above_mbmi ) ;
 const MV_REFERENCE_FRAME vrfa = a_sg ? above_mbmi -> ref_frame [ 0 ] : above_mbmi -> ref_frame [ var_ref_idx ] ;
 const MV_REFERENCE_FRAME vrfl = l_sg ? left_mbmi -> ref_frame [ 0 ] : left_mbmi -> ref_frame [ var_ref_idx ] ;
 if ( vrfa == vrfl && cm -> comp_var_ref [ 1 ] == vrfa ) {
 pred_context = 0 ;
 }
 else if ( l_sg && a_sg ) {
 if ( ( vrfa == cm -> comp_fixed_ref && vrfl == cm -> comp_var_ref [ 0 ] ) || ( vrfl == cm -> comp_fixed_ref && vrfa == cm -> comp_var_ref [ 0 ] ) ) pred_context = 4 ;
 else if ( vrfa == vrfl ) pred_context = 3 ;
 else pred_context = 1 ;
 }
 else if ( l_sg || a_sg ) {
 const MV_REFERENCE_FRAME vrfc = l_sg ? vrfa : vrfl ;
 const MV_REFERENCE_FRAME rfs = a_sg ? vrfa : vrfl ;
 if ( vrfc == cm -> comp_var_ref [ 1 ] && rfs != cm -> comp_var_ref [ 1 ] ) pred_context = 1 ;
 else if ( rfs == cm -> comp_var_ref [ 1 ] && vrfc != cm -> comp_var_ref [ 1 ] ) pred_context = 2 ;
 else pred_context = 4 ;
 }
 else if ( vrfa == vrfl ) {
 pred_context = 4 ;
 }
 else {
 pred_context = 2 ;
 }
 }
 }
 else if ( above_in_image || left_in_image ) {
 const MB_MODE_INFO * edge_mbmi = above_in_image ? above_mbmi : left_mbmi ;
 if ( ! is_inter_block ( edge_mbmi ) ) {
 pred_context = 2 ;
 }
 else {
 if ( has_second_ref ( edge_mbmi ) ) pred_context = 4 * ( edge_mbmi -> ref_frame [ var_ref_idx ] != cm -> comp_var_ref [ 1 ] ) ;
 else pred_context = 3 * ( edge_mbmi -> ref_frame [ 0 ] != cm -> comp_var_ref [ 1 ] ) ;
 }
 }
 else {
 pred_context = 2 ;
 }
 assert ( pred_context >= 0 && pred_context < REF_CONTEXTS ) ;
 return pred_context ;
 }