static guint find_tail ( body_parts * * body_parts_array , guint16 tsn ) {
 guint length = 0 ;
 for ( tsn = ( tsn + 1 ) % MAX_TSN ;
 body_parts_array [ tsn ] -> middle != NULL ;
 tsn = ( tsn + 1 ) % MAX_TSN ) length += body_parts_array [ tsn ] -> middle -> length ;
 if ( body_parts_array [ tsn ] -> tail != NULL ) return length + body_parts_array [ tsn ] -> tail -> length ;
 return 0 ;
 }