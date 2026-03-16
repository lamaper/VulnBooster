const char * hb_blob_get_data ( hb_blob_t * blob , unsigned int * length ) {
 if ( length ) * length = blob -> length ;
 return blob -> data ;
 }