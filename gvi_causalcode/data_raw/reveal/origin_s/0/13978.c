static void init_frag ( tvbuff_t * tvb , body_parts * bp , guint length , guint offset , guint32 frame_num , guint16 tsn , guint8 type ) {
 mac_is_fragment * frag = wmem_new ( wmem_file_scope ( ) , mac_is_fragment ) ;
 frag -> type = type ;
 frag -> length = length ;
 frag -> data = ( guint8 * ) g_malloc ( length ) ;
 frag -> frame_num = frame_num ;
 frag -> tsn = tsn ;
 frag -> next = NULL ;
 switch ( type ) {
 case MAC_IS_HEAD : DISSECTOR_ASSERT ( bp -> head == NULL ) ;
 bp -> head = frag ;
 break ;
 case MAC_IS_MIDDLE : DISSECTOR_ASSERT ( bp -> middle == NULL ) ;
 bp -> middle = frag ;
 break ;
 case MAC_IS_TAIL : DISSECTOR_ASSERT ( bp -> tail == NULL ) ;
 bp -> tail = frag ;
 break ;
 }
 tvb_memcpy ( tvb , frag -> data , offset , length ) ;
 }