static bool astream_want_attachment ( struct attachment_istream * astream , struct message_part * part ) {
 struct istream_attachment_header ahdr ;
 if ( ( part -> flags & MESSAGE_PART_FLAG_MULTIPART ) != 0 ) {
 return FALSE ;
 }
 if ( astream -> set . want_attachment == NULL ) return TRUE ;
 i_zero ( & ahdr ) ;
 ahdr . part = part ;
 ahdr . content_type = astream -> part . content_type ;
 ahdr . content_disposition = astream -> part . content_disposition ;
 return astream -> set . want_attachment ( & ahdr , astream -> context ) ;
 }