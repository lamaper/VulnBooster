char * _ksba_oid_node_to_str ( const unsigned char * image , AsnNode node ) {
 if ( ! node || node -> type != TYPE_OBJECT_ID || node -> off == - 1 ) return NULL ;
 return ksba_oid_to_str ( image + node -> off + node -> nhdr , node -> len ) ;
 }