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