void vp9_build_nmv_cost_table ( int * mvjoint , int * mvcost [ 2 ] , const nmv_context * ctx , int usehp ) {
 vp9_cost_tokens ( mvjoint , ctx -> joints , vp9_mv_joint_tree ) ;
 build_nmv_component_cost_table ( mvcost [ 0 ] , & ctx -> comps [ 0 ] , usehp ) ;
 build_nmv_component_cost_table ( mvcost [ 1 ] , & ctx -> comps [ 1 ] , usehp ) ;
 }