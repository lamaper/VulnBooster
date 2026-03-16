static struct GuidPropertySet * GuidPropertySet_find_guid ( const e_guid_t * guid ) {
 unsigned i ;
 for ( i = 0 ;
 i < array_length ( GuidPropertySet ) ;
 i ++ ) {
 if ( guid_cmp ( & GuidPropertySet [ i ] . guid , guid ) == 0 ) {
 return & GuidPropertySet [ i ] ;
 }
 }
 return NULL ;
 }