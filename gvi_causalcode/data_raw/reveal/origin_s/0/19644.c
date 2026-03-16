static int get_fixed_vtype_dataize ( enum vType vtype ) {
 struct vtype_data * vt_type = vType_get_type ( vtype ) ;
 if ( vt_type ) {
 return vt_type -> size ;
 }
 return - 1 ;
 }