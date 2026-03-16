hb_graphite2_shaper_face_data_t * _hb_graphite2_shaper_face_data_create ( hb_face_t * face ) {
 hb_blob_t * silf_blob = face -> reference_table ( HB_GRAPHITE2_TAG_SILF ) ;
 if ( ! hb_blob_get_length ( silf_blob ) ) {
 hb_blob_destroy ( silf_blob ) ;
 return NULL ;
 }
 hb_blob_destroy ( silf_blob ) ;
 hb_graphite2_shaper_face_data_t * data = ( hb_graphite2_shaper_face_data_t * ) calloc ( 1 , sizeof ( hb_graphite2_shaper_face_data_t ) ) ;
 if ( unlikely ( ! data ) ) return NULL ;
 data -> face = face ;
 data -> grface = gr_make_face ( data , & hb_graphite2_get_table , gr_face_preloadAll ) ;
 if ( unlikely ( ! data -> grface ) ) {
 free ( data ) ;
 return NULL ;
 }
 return data ;
 }