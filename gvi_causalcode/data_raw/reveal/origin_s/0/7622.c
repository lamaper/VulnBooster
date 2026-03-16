gr_font # include "hb-shaper-impl-private.hh" # include "hb-graphite2.h" # include < graphite2 / Segment . h > HB_SHAPER_DATA_ENSURE_DECLARE ( graphite2 , face ) HB_SHAPER_DATA_ENSURE_DECLARE ( graphite2 , font ) typedef struct hb_graphite2_tablelist_t {
 struct hb_graphite2_tablelist_t * next ;
 hb_blob_t * blob ;
 unsigned int tag ;
 }
 hb_graphite2_tablelist_t ;
 struct hb_graphite2_shaper_face_data_t {
 hb_face_t * face ;
 gr_face * grface ;
 hb_graphite2_tablelist_t * tlist ;
 }
 ;
 static const void * hb_graphite2_get_table ( const void * data , unsigned int tag , size_t * len ) {
 hb_graphite2_shaper_face_data_t * face_data = ( hb_graphite2_shaper_face_data_t * ) data ;
 hb_graphite2_tablelist_t * tlist = face_data -> tlist ;
 hb_blob_t * blob = NULL ;
 for ( hb_graphite2_tablelist_t * p = tlist ;
 p ;
 p = p -> next ) if ( p -> tag == tag ) {
 blob = p -> blob ;
 break ;
 }
 if ( unlikely ( ! blob ) ) {
 blob = face_data -> face -> reference_table ( tag ) ;
 hb_graphite2_tablelist_t * p = ( hb_graphite2_tablelist_t * ) calloc ( 1 , sizeof ( hb_graphite2_tablelist_t ) ) ;
 if ( unlikely ( ! p ) ) {
 hb_blob_destroy ( blob ) ;
 return NULL ;
 }
 p -> blob = blob ;
 p -> tag = tag ;
 p -> next = face_data -> tlist ;
 face_data -> tlist = p ;
 }
 unsigned int tlen ;
 const char * d = hb_blob_get_data ( blob , & tlen ) ;
 * len = tlen ;
 return d ;
 }
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
 gr_face * hb_graphite2_face_get_gr_face ( hb_face_t * face ) {
 if ( unlikely ( ! hb_graphite2_shaper_face_data_ensure ( face ) ) ) return NULL ;
 return HB_SHAPER_DATA_GET ( face ) -> grface ;
 }
 static float hb_graphite2_get_advance ( const void * hb_font , unsigned short gid ) {
 return ( ( hb_font_t * ) hb_font ) -> get_glyph_h_advance ( gid ) ;
 }
 hb_graphite2_shaper_font_data_t * _hb_graphite2_shaper_font_data_create ( hb_font_t * font ) {
 if ( unlikely ( ! hb_graphite2_shaper_face_data_ensure ( font -> face ) ) ) return NULL ;
 hb_face_t * face = font -> face ;
 hb_graphite2_shaper_face_data_t * face_data = HB_SHAPER_DATA_GET ( face ) ;
 return gr_make_font_with_advance_fn ( font -> x_scale , font , & hb_graphite2_get_advance , face_data -> grface ) ;
 }