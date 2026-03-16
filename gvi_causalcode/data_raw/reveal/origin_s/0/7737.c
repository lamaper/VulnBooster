void hb_face_destroy ( hb_face_t * face ) {
 if ( ! hb_object_destroy ( face ) ) return ;
 for ( hb_face_t : : plan_node_t * node = face -> shape_plans ;
 node ;
 ) {
 hb_face_t : : plan_node_t * next = node -> next ;
 hb_shape_plan_destroy ( node -> shape_plan ) ;
 free ( node ) ;
 node = next ;
 }


 free ( face ) ;
 }