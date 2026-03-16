static gint round_to_2byte ( gint current_offset , gint starting_offset ) {
 gint length = current_offset - starting_offset ;
 return starting_offset + ROUND_TO_2BYTE ( length ) ;
 }