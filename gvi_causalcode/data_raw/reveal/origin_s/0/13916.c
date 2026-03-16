static gint pvfs2_io_tracking_equal ( gconstpointer k1 , gconstpointer k2 ) {
 const pvfs2_io_tracking_key_t * key1 = ( const pvfs2_io_tracking_key_t * ) k1 ;
 const pvfs2_io_tracking_key_t * key2 = ( const pvfs2_io_tracking_key_t * ) k2 ;
 return ( key1 -> tag == key2 -> tag ) ;
 }