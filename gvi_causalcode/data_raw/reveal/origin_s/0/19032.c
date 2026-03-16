static gboolean mac_is_fragment_equal ( gconstpointer a , gconstpointer b ) {
 const mac_is_fragment * x = ( const mac_is_fragment * ) a , * y = ( const mac_is_fragment * ) b ;
 return x -> frame_num == y -> frame_num && x -> tsn == y -> tsn && x -> type == y -> type ;
 }