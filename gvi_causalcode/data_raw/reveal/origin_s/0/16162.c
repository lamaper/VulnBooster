void hb_blob_make_immutable ( hb_blob_t * blob ) {
 if ( hb_object_is_inert ( blob ) ) return ;
 blob -> immutable = true ;
 }