static int astream_base64_decode_lf ( struct attachment_istream_part * part ) {
 if ( part -> base64_have_crlf && part -> base64_state != BASE64_STATE_CR ) {
 return - 1 ;
 }
 part -> base64_state = BASE64_STATE_0 ;
 if ( part -> cur_base64_blocks < part -> base64_line_blocks ) {
 part -> base64_state = BASE64_STATE_EOM ;
 return 0 ;
 }
 else if ( part -> base64_line_blocks == 0 ) {
 if ( part -> cur_base64_blocks == 0 ) return - 1 ;
 part -> base64_line_blocks = part -> cur_base64_blocks ;
 }
 else if ( part -> cur_base64_blocks == part -> base64_line_blocks ) {
 }
 else {
 return - 1 ;
 }
 part -> cur_base64_blocks = 0 ;
 return 1 ;
 }