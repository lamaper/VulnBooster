static void splay_move_to_root ( clump_t * x , gs_ref_memory_t * mem ) {
 clump_t * y , * z ;
 if ( x == NULL ) return ;
 while ( ( y = x -> parent ) != NULL ) {
 if ( ( z = y -> parent ) != NULL ) {
 x -> parent = z -> parent ;
 if ( x -> parent ) {
 if ( x -> parent -> left == z ) x -> parent -> left = x ;
 else x -> parent -> right = x ;
 }
 y -> parent = x ;
 if ( y -> left == x ) {
 if ( z -> left == y ) {
 y -> left = x -> right ;
 if ( y -> left ) y -> left -> parent = y ;
 z -> left = y -> right ;
 if ( z -> left ) z -> left -> parent = z ;
 y -> right = z ;
 z -> parent = y ;
 }
 else {
 z -> right = x -> left ;
 if ( z -> right ) z -> right -> parent = z ;
 y -> left = x -> right ;
 if ( y -> left ) y -> left -> parent = y ;
 x -> left = z ;
 z -> parent = x ;
 }
 x -> right = y ;
 }
 else {
 if ( z -> left == y ) {
 y -> right = x -> left ;
 if ( y -> right ) y -> right -> parent = y ;
 z -> left = x -> right ;
 if ( z -> left ) z -> left -> parent = z ;
 x -> right = z ;
 z -> parent = x ;
 }
 else {
 z -> right = y -> left ;
 if ( z -> right ) z -> right -> parent = z ;
 y -> right = x -> left ;
 if ( y -> right ) y -> right -> parent = y ;
 y -> left = z ;
 z -> parent = y ;
 }
 x -> left = y ;
 }
 }
 else {
 x -> parent = NULL ;
 y -> parent = x ;
 if ( y -> left == x ) {
 y -> left = x -> right ;
 if ( y -> left ) y -> left -> parent = y ;
 x -> right = y ;
 }
 else {
 y -> right = x -> left ;
 if ( y -> right ) y -> right -> parent = y ;
 x -> left = y ;
 }
 }
 }
 mem -> root = x ;
 }