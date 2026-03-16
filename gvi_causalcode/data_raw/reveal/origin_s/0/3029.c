static int astream_end_of_part ( struct attachment_istream * astream , const char * * error_r ) {
 struct attachment_istream_part * part = & astream -> part ;
 size_t old_size ;
 int ret = 0 ;
 switch ( part -> state ) {
 case MAIL_ATTACHMENT_STATE_NO : break ;
 case MAIL_ATTACHMENT_STATE_MAYBE : if ( part -> part_buf != NULL ) {
 stream_add_data ( astream , part -> part_buf -> data , part -> part_buf -> used ) ;
 ret = part -> part_buf -> used > 0 ? 1 : 0 ;
 }
 break ;
 case MAIL_ATTACHMENT_STATE_YES : old_size = astream -> istream . pos - astream -> istream . skip ;
 if ( astream_part_finish ( astream , error_r ) < 0 ) ret = - 1 ;
 else {
 ret = astream -> istream . pos - astream -> istream . skip - old_size ;
 }
 break ;
 }
 part -> state = MAIL_ATTACHMENT_STATE_NO ;
 astream_part_reset ( astream ) ;
 return ret ;
 }