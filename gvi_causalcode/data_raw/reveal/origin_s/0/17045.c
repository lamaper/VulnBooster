static bool _try_writable ( hb_blob_t * blob ) {
 if ( blob -> immutable ) return false ;
 if ( blob -> mode == HB_MEMORY_MODE_WRITABLE ) return true ;
 if ( blob -> mode == HB_MEMORY_MODE_READONLY_MAY_MAKE_WRITABLE && _try_writable_inplace ( blob ) ) return true ;
 if ( blob -> mode == HB_MEMORY_MODE_WRITABLE ) return true ;
 DEBUG_MSG_FUNC ( BLOB , blob , "current data is -> %p\n" , blob -> data ) ;
 char * new_data ;
 new_data = ( char * ) malloc ( blob -> length ) ;
 if ( unlikely ( ! new_data ) ) return false ;
 DEBUG_MSG_FUNC ( BLOB , blob , "dupped successfully -> %p\n" , blob -> data ) ;
 memcpy ( new_data , blob -> data , blob -> length ) ;
 _hb_blob_destroy_user_data ( blob ) ;
 blob -> mode = HB_MEMORY_MODE_WRITABLE ;
 blob -> data = new_data ;
 blob -> user_data = new_data ;
 blob -> destroy = free ;
 return true ;
 }