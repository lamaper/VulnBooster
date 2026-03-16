static bool add_line ( String & buffer , char * line , ulong line_length , char * in_string , bool * ml_comment , bool truncated ) {
 uchar inchar ;
 char buff [ 80 ] , * pos , * out ;
 COMMANDS * com ;
 bool need_space = 0 ;
 bool ss_comment = 0 ;
 DBUG_ENTER ( "add_line" ) ;
 if ( ! line [ 0 ] && buffer . is_empty ( ) ) DBUG_RETURN ( 0 ) ;


 for ( pos = out = line ;
 pos < end_of_line ;
 pos ++ ) {
 inchar = ( uchar ) * pos ;
 if ( ! preserve_comments ) {
 if ( my_isspace ( charset_info , inchar ) && ( out == line ) && buffer . is_empty ( ) ) continue ;
 }

 if ( use_mb ( charset_info ) && ( length = my_ismbchar ( charset_info , pos , end_of_line ) ) ) {
 if ( ! * ml_comment || preserve_comments ) {
 while ( length -- ) * out ++ = * pos ++ ;
 pos -- ;
 }
 else pos += length - 1 ;
 continue ;
 }

 if ( ! ( inchar = ( uchar ) * ++ pos ) ) break ;
 if ( * in_string || inchar == 'N' ) {
 * out ++ = '\\' ;
 * out ++ = ( char ) inchar ;
 continue ;
 }
 if ( ( com = find_command ( ( char ) inchar ) ) ) {
 if ( out != line ) {
 buffer . append ( line , ( uint ) ( out - line ) ) ;
 out = line ;
 }
 if ( ( * com -> func ) ( & buffer , pos - 1 ) > 0 ) DBUG_RETURN ( 1 ) ;
 if ( com -> takes_params ) {
 if ( ss_comment ) {
 for ( pos ++ ;
 * pos && ( * pos != '*' || * ( pos + 1 ) != '/' ) ;
 pos ++ ) ;
 pos -- ;
 }
 else {
 for ( pos ++ ;
 * pos && ( * pos != * delimiter || ! is_prefix ( pos + 1 , delimiter + 1 ) ) ;
 pos ++ ) ;
 if ( ! * pos ) pos -- ;
 else pos += delimiter_length - 1 ;
 }
 }
 }
 else {
 sprintf ( buff , "Unknown command '\\%c'." , inchar ) ;
 if ( put_info ( buff , INFO_ERROR ) > 0 ) DBUG_RETURN ( 1 ) ;
 * out ++ = '\\' ;
 * out ++ = ( char ) inchar ;
 continue ;
 }
 }
 else if ( ! * ml_comment && ! * in_string && is_prefix ( pos , delimiter ) ) {
 pos += delimiter_length ;
 if ( preserve_comments ) {
 while ( my_isspace ( charset_info , * pos ) ) * out ++ = * pos ++ ;
 }
 if ( out != line ) {
 buffer . append ( line , ( uint32 ) ( out - line ) ) ;
 out = line ;
 }
 if ( preserve_comments && ( ( * pos == '#' ) || ( ( * pos == '-' ) && ( pos [ 1 ] == '-' ) && my_isspace ( charset_info , pos [ 2 ] ) ) ) ) {
 buffer . append ( pos ) ;
 pos += strlen ( pos ) ;
 }
 pos -- ;
 if ( ( com = find_command ( buffer . c_ptr ( ) ) ) ) {
 if ( ( * com -> func ) ( & buffer , buffer . c_ptr ( ) ) > 0 ) DBUG_RETURN ( 1 ) ;
 }
 else {
 if ( com_go ( & buffer , 0 ) > 0 ) DBUG_RETURN ( 1 ) ;
 }
 buffer . length ( 0 ) ;
 }
 else if ( ! * ml_comment && ( ! * in_string && ( inchar == '#' || ( inchar == '-' && pos [ 1 ] == '-' && ( ( my_isspace ( charset_info , pos [ 2 ] ) || ! pos [ 2 ] ) || ( buffer . is_empty ( ) && out == line ) ) ) ) ) ) {
 if ( out != line ) {
 buffer . append ( line , ( uint32 ) ( out - line ) ) ;
 out = line ;
 }
 if ( preserve_comments ) {
 bool started_with_nothing = ! buffer . length ( ) ;
 buffer . append ( pos ) ;
 if ( started_with_nothing ) {
 if ( com_go ( & buffer , 0 ) > 0 ) DBUG_RETURN ( 1 ) ;
 buffer . length ( 0 ) ;
 }
 }
 break ;
 }
 else if ( ! * in_string && inchar == '/' && * ( pos + 1 ) == '*' && ! ( * ( pos + 2 ) == '!' || ( * ( pos + 2 ) == 'M' && * ( pos + 3 ) == '!' ) ) ) {
 if ( preserve_comments ) {
 * out ++ = * pos ++ ;
 * out ++ = * pos ;
 }
 else pos ++ ;
 * ml_comment = 1 ;
 if ( out != line ) {
 buffer . append ( line , ( uint ) ( out - line ) ) ;
 out = line ;
 }
 }
 else if ( * ml_comment && ! ss_comment && inchar == '*' && * ( pos + 1 ) == '/' ) {
 if ( preserve_comments ) {
 * out ++ = * pos ++ ;
 * out ++ = * pos ;
 }
 else pos ++ ;
 * ml_comment = 0 ;
 if ( out != line ) {
 buffer . append ( line , ( uint32 ) ( out - line ) ) ;
 out = line ;
 }
 need_space = 1 ;
 }
 else {
 if ( ! * in_string && inchar == '/' && * ( pos + 1 ) == '*' && * ( pos + 2 ) == '!' ) ss_comment = 1 ;
 else if ( ! * in_string && ss_comment && inchar == '*' && * ( pos + 1 ) == '/' ) ss_comment = 0 ;
 if ( inchar == * in_string ) * in_string = 0 ;
 else if ( ! * ml_comment && ! * in_string && ( inchar == '\'' || inchar == '"' || inchar == '`' ) ) * in_string = ( char ) inchar ;
 if ( ! * ml_comment || preserve_comments ) {
 if ( need_space && ! my_isspace ( charset_info , ( char ) inchar ) ) * out ++ = ' ' ;
 need_space = 0 ;
 * out ++ = ( char ) inchar ;
 }
 }
 }
 if ( out != line || ! buffer . is_empty ( ) ) {
 uint length = ( uint ) ( out - line ) ;
 if ( ! truncated && ( ! is_delimiter_command ( line , length ) || ( * in_string || * ml_comment ) ) ) {
 * out ++ = '\n' ;
 length ++ ;
 }
 if ( buffer . length ( ) + length >= buffer . alloced_length ( ) ) buffer . realloc ( buffer . length ( ) + length + IO_SIZE ) ;
 if ( ( ! * ml_comment || preserve_comments ) && buffer . append ( line , length ) ) DBUG_RETURN ( 1 ) ;
 }
 DBUG_RETURN ( 0 ) ;
 }