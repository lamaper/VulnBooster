static gboolean mac_is_channel_equal ( gconstpointer a , gconstpointer b ) {
 const mac_is_channel * x = ( const mac_is_channel * ) a , * y = ( const mac_is_channel * ) b ;
 return x -> lchid == y -> lchid && x -> ueid == y -> ueid ;
 }