hb_blob_t * hb_blob_create ( const char * data , unsigned int length , hb_memory_mode_t mode , void * user_data , hb_destroy_func_t destroy ) {
 hb_blob_t * blob ;
 if ( ! length || ! ( blob = hb_object_create < hb_blob_t > ( ) ) ) {
 if ( destroy ) destroy ( user_data ) ;
 return hb_blob_get_empty ( ) ;
 }
 blob -> data = data ;
 blob -> length = length ;
 blob -> mode = mode ;
 blob -> user_data = user_data ;
 blob -> destroy = destroy ;
 if ( blob -> mode == HB_MEMORY_MODE_DUPLICATE ) {
 blob -> mode = HB_MEMORY_MODE_READONLY ;
 if ( ! _try_writable ( blob ) ) {
 hb_blob_destroy ( blob ) ;
 return hb_blob_get_empty ( ) ;
 }
 }
 return blob ;
 }