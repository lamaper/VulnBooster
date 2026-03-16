static void mac_is_copy ( mac_is_sdu * sdu , mac_is_fragment * frag , guint total_length , gboolean reverse ) {
 DISSECTOR_ASSERT ( sdu -> length + frag -> length <= total_length ) ;
 if ( reverse ) {
 memcpy ( sdu -> data + total_length - frag -> length - sdu -> length , frag -> data , frag -> length ) ;
 }
 else {
 memcpy ( sdu -> data + sdu -> length , frag -> data , frag -> length ) ;
 }
 sdu -> length += frag -> length ;
 g_free ( frag -> data ) ;
 }