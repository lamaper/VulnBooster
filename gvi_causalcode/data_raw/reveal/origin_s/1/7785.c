static hb_feature_t * feature_reference ( hb_feature_t * g ) {
 hb_feature_t * c = ( hb_feature_t * ) calloc ( 1 , sizeof ( hb_feature_t ) ) ;
 if ( unlikely ( ! c ) ) return NULL ;
 * c = * g ;
 return c ;
 }