hb_blob_t * hb_blob_create_sub_blob ( hb_blob_t * parent , unsigned int offset , unsigned int length ) {
 hb_blob_t * blob ;
 if ( ! length || offset >= parent -> length ) return hb_blob_get_empty ( ) ;
 hb_blob_make_immutable ( parent ) ;
 blob = hb_blob_create ( parent -> data + offset , MIN ( length , parent -> length - offset ) , HB_MEMORY_MODE_READONLY , hb_blob_reference ( parent ) , ( hb_destroy_func_t ) hb_blob_destroy ) ;
 return blob ;
 }