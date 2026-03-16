static FT_Error cid_hex_to_binary ( FT_Byte * data , FT_Long data_len , FT_ULong offset , CID_Face face ) {
 FT_Stream stream = face -> root . stream ;
 FT_Error error ;
 FT_Byte buffer [ 256 ] ;
 FT_Byte * p , * plimit ;
 FT_Byte * d , * dlimit ;
 FT_Byte val ;
 FT_Bool upper_nibble , done ;
 if ( FT_STREAM_SEEK ( offset ) ) goto Exit ;
 d = data ;
 dlimit = d + data_len ;
 p = buffer ;
 plimit = p ;
 upper_nibble = 1 ;
 done = 0 ;
 while ( d < dlimit ) {
 if ( p >= plimit ) {
 FT_ULong oldpos = FT_STREAM_POS ( ) ;
 FT_ULong size = stream -> size - oldpos ;
 if ( size == 0 ) {
 error = FT_THROW ( Syntax_Error ) ;
 goto Exit ;
 }
 if ( FT_STREAM_READ ( buffer , 256 > size ? size : 256 ) ) goto Exit ;
 p = buffer ;
 plimit = p + FT_STREAM_POS ( ) - oldpos ;
 }
 if ( ft_isdigit ( * p ) ) val = ( FT_Byte ) ( * p - '0' ) ;
 else if ( * p >= 'a' && * p <= 'f' ) val = ( FT_Byte ) ( * p - 'a' ) ;
 else if ( * p >= 'A' && * p <= 'F' ) val = ( FT_Byte ) ( * p - 'A' + 10 ) ;
 else if ( * p == ' ' || * p == '\t' || * p == '\r' || * p == '\n' || * p == '\f' || * p == '\0' ) {
 p ++ ;
 continue ;
 }
 else if ( * p == '>' ) {
 val = 0 ;
 done = 1 ;
 }
 else {
 error = FT_THROW ( Syntax_Error ) ;
 goto Exit ;
 }
 if ( upper_nibble ) * d = ( FT_Byte ) ( val << 4 ) ;
 else {
 * d = ( FT_Byte ) ( * d + val ) ;
 d ++ ;
 }
 upper_nibble = ( FT_Byte ) ( 1 - upper_nibble ) ;
 if ( done ) break ;
 p ++ ;
 }
 error = FT_Err_Ok ;
 Exit : return error ;
 }