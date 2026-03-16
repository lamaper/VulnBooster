static void handle_lockprop_ctx ( struct xml_ctx * ctx , int tag_closed ) {
 int * lock_flags = ( int * ) ctx -> userData ;
 if ( tag_closed ) {
 if ( ! strcmp ( ctx -> name , DAV_CTX_LOCKENTRY ) ) {
 if ( ( * lock_flags & DAV_PROP_LOCKEX ) && ( * lock_flags & DAV_PROP_LOCKWR ) ) {
 * lock_flags |= DAV_LOCK_OK ;
 }
 * lock_flags &= DAV_LOCK_OK ;
 }
 else if ( ! strcmp ( ctx -> name , DAV_CTX_LOCKTYPE_WRITE ) ) {
 * lock_flags |= DAV_PROP_LOCKWR ;
 }
 else if ( ! strcmp ( ctx -> name , DAV_CTX_LOCKTYPE_EXCLUSIVE ) ) {
 * lock_flags |= DAV_PROP_LOCKEX ;
 }
 }
 }