static struct vtype_data * vType_get_type ( guint16 t ) {
 unsigned i ;
 t = ( t & 0xFF ) ;
 for ( i = 0 ;
 i < array_length ( VT_TYPE ) ;
 i ++ ) {
 if ( t == VT_TYPE [ i ] . tag ) {
 return & VT_TYPE [ i ] ;
 }
 }
 return NULL ;
 }