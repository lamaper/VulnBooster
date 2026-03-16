static hb_segment_properties_t * segment_properties_reference ( hb_segment_properties_t * g ) {
 hb_segment_properties_t * c = ( hb_segment_properties_t * ) calloc ( 1 , sizeof ( hb_segment_properties_t ) ) ;
 if ( unlikely ( ! c ) ) return NULL ;
 * c = * g ;
 return c ;
 }