void _hb_graphite2_shaper_face_data_destroy ( hb_graphite2_shaper_face_data_t * data ) {
 hb_graphite2_tablelist_t * tlist = data -> tlist ;
 while ( tlist ) {
 hb_graphite2_tablelist_t * old = tlist ;
 hb_blob_destroy ( tlist -> blob ) ;
 tlist = tlist -> next ;
 free ( old ) ;
 }
 gr_face_destroy ( data -> grface ) ;
 free ( data ) ;
 }