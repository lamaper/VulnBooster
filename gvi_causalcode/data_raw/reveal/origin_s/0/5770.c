static void splay_insert ( clump_t * cp , gs_ref_memory_t * mem ) {
 clump_t * node = NULL ;
 clump_t * * root = & mem -> root ;
 while ( * root ) {
 node = * root ;
 if ( PTR_LT ( cp -> cbase , node -> cbase ) ) {
 root = & node -> left ;
 }
 else {
 root = & node -> right ;
 }
 }
 * root = cp ;
 cp -> left = NULL ;
 cp -> right = NULL ;
 cp -> parent = node ;
 splay_move_to_root ( cp , mem ) ;
 }