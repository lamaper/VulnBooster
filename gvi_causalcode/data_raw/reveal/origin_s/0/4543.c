static int cost_mv_ref ( const VP9_COMP * cpi , PREDICTION_MODE mode , int mode_context ) {
 assert ( is_inter_mode ( mode ) ) ;
 return cpi -> inter_mode_cost [ mode_context ] [ INTER_OFFSET ( mode ) ] ;
 }