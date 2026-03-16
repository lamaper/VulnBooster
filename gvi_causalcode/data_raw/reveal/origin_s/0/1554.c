static guint find_head ( body_parts * * body_parts_array , guint16 * tsn ) {
 guint length = 0 ;
 * tsn = ( * tsn == 0 ) ? ( guint16 ) ( MAX_TSN - 1 ) : ( * tsn ) - 1 ;
 for ( ;
 body_parts_array [ * tsn ] -> middle != NULL ;
 * tsn = ( * tsn == 0 ) ? ( guint16 ) ( MAX_TSN - 1 ) : ( * tsn ) - 1 ) length += body_parts_array [ * tsn ] -> middle -> length ;
 if ( body_parts_array [ * tsn ] -> head != NULL ) return length + body_parts_array [ * tsn ] -> head -> length ;
 return 0 ;
 }