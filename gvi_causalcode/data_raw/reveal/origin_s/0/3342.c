static bool _try_writable_inplace ( hb_blob_t * blob ) {
 DEBUG_MSG_FUNC ( BLOB , blob , "making writable inplace\n" ) ;
 if ( _try_make_writable_inplace_unix ( blob ) ) return true ;
 DEBUG_MSG_FUNC ( BLOB , blob , "making writable -> FAILED\n" ) ;
 blob -> mode = HB_MEMORY_MODE_READONLY ;
 return false ;
 }