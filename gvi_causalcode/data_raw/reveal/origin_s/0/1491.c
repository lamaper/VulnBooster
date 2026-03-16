char * hb_blob_get_data_writable ( hb_blob_t * blob , unsigned int * length ) {
 if ( ! _try_writable ( blob ) ) {
 if ( length ) * length = 0 ;
 return NULL ;
 }
 if ( length ) * length = blob -> length ;
 return const_cast < char * > ( blob -> data ) ;
 }