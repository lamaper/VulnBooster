static gboolean set_pinfo_desegment ( packet_info * pinfo , gint next_offset , gint addition_bytes_needed ) {
 if ( pinfo -> can_desegment ) {
 pinfo -> desegment_offset = next_offset ;
 pinfo -> desegment_len = addition_bytes_needed ;
 return TRUE ;
 }
 return FALSE ;
 }