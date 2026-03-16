static guint mac_is_channel_hash ( gconstpointer key ) {
 const mac_is_channel * ch = ( const mac_is_channel * ) key ;
 return ( ch -> ueid << 4 ) | ch -> lchid ;
 }