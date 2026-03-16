static int astream_try_base64_decode_char ( struct attachment_istream_part * part , size_t pos , char chr ) {
 switch ( part -> base64_state ) {
 case BASE64_STATE_0 : if ( base64_is_valid_char ( chr ) ) part -> base64_state ++ ;
 else if ( chr == '\r' ) part -> base64_state = BASE64_STATE_CR ;
 else if ( chr == '\n' ) {
 return astream_base64_decode_lf ( part ) ;
 }
 else {
 return - 1 ;
 }
 break ;
 case BASE64_STATE_1 : if ( ! base64_is_valid_char ( chr ) ) return - 1 ;
 part -> base64_state ++ ;
 break ;
 case BASE64_STATE_2 : if ( base64_is_valid_char ( chr ) ) part -> base64_state ++ ;
 else if ( chr == '=' ) part -> base64_state = BASE64_STATE_EOB ;
 else return - 1 ;
 break ;
 case BASE64_STATE_3 : part -> base64_bytes = part -> temp_output -> offset + pos + 1 ;
 if ( base64_is_valid_char ( chr ) ) {
 part -> base64_state = BASE64_STATE_0 ;
 part -> cur_base64_blocks ++ ;
 }
 else if ( chr == '=' ) {
 part -> base64_state = BASE64_STATE_EOM ;
 part -> cur_base64_blocks ++ ;
 if ( part -> cur_base64_blocks > part -> base64_line_blocks && part -> base64_line_blocks > 0 ) {
 return - 1 ;
 }
 return 0 ;
 }
 else {
 return - 1 ;
 }
 break ;
 case BASE64_STATE_CR : if ( chr != '\n' ) return - 1 ;
 if ( ! part -> base64_have_crlf ) {
 if ( part -> base64_line_blocks != 0 ) {
 return - 1 ;
 }
 part -> base64_have_crlf = TRUE ;
 }
 return astream_base64_decode_lf ( part ) ;
 case BASE64_STATE_EOB : if ( chr != '=' ) return - 1 ;
 part -> base64_bytes = part -> temp_output -> offset + pos + 1 ;
 part -> base64_state = BASE64_STATE_EOM ;
 part -> cur_base64_blocks ++ ;
 if ( part -> cur_base64_blocks > part -> base64_line_blocks && part -> base64_line_blocks > 0 ) {
 return - 1 ;
 }
 return 0 ;
 case BASE64_STATE_EOM : i_unreached ( ) ;
 }
 return 1 ;
 }