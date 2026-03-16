static guint pvfs2_io_tracking_hash ( gconstpointer k ) {
 const pvfs2_io_tracking_key_t * key = ( const pvfs2_io_tracking_key_t * ) k ;
 return ( guint ) ( ( key -> tag >> 32 ) ^ ( ( guint32 ) key -> tag ) ) ;
 }