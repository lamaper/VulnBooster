static void append_transform ( struct qcms_modular_transform * transform , struct qcms_modular_transform * * * next_transform ) {
 * * next_transform = transform ;
 while ( transform ) {
 * next_transform = & ( transform -> next_transform ) ;
 transform = transform -> next_transform ;
 }
 }