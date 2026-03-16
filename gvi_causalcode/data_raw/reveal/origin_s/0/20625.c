static inline hb_bool_t hb_shape_plan_user_features_match ( const hb_shape_plan_t * shape_plan , const hb_shape_plan_proposal_t * proposal ) {
 if ( proposal -> num_user_features != shape_plan -> num_user_features ) return false ;
 for ( unsigned int i = 0 , n = proposal -> num_user_features ;
 i < n ;
 i ++ ) if ( proposal -> user_features [ i ] . tag != shape_plan -> user_features [ i ] . tag || proposal -> user_features [ i ] . value != shape_plan -> user_features [ i ] . value || proposal -> user_features [ i ] . start != shape_plan -> user_features [ i ] . start || proposal -> user_features [ i ] . end != shape_plan -> user_features [ i ] . end ) return false ;
 return true ;
 }