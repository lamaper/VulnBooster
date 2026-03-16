static inline hb_bool_t hb_non_global_user_features_present ( const hb_feature_t * user_features , unsigned int num_user_features ) {
 while ( num_user_features ) if ( user_features -> start != 0 || user_features -> end != ( unsigned int ) - 1 ) return true ;
 else num_user_features -- , user_features ++ ;
 return false ;
 }