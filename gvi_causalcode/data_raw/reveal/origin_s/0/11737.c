static void _hb_blob_destroy_user_data ( hb_blob_t * blob ) {
 if ( blob -> destroy ) {
 blob -> destroy ( blob -> user_data ) ;
 blob -> user_data = NULL ;
 blob -> destroy = NULL ;
 }
 }