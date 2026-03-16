static guint mac_is_fragment_hash ( gconstpointer key ) {
 const mac_is_fragment * frag = ( const mac_is_fragment * ) key ;
 return ( frag -> frame_num << 2 ) | frag -> type ;
 }