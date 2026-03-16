static struct qcms_modular_transform * reverse_transform ( struct qcms_modular_transform * transform ) {
 struct qcms_modular_transform * prev_transform = NULL ;
 while ( transform != NULL ) {
 struct qcms_modular_transform * next_transform = transform -> next_transform ;
 transform -> next_transform = prev_transform ;
 prev_transform = transform ;
 transform = next_transform ;
 }
 return prev_transform ;
 }