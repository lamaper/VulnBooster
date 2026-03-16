static int y4m_parse_tags ( y4m_input * _y4m , char * _tags ) {
 int got_w ;
 int got_h ;
 int got_fps ;
 int got_interlace ;
 int got_par ;
 int got_chroma ;
 char * p ;
 char * q ;
 got_w = got_h = got_fps = got_interlace = got_par = got_chroma = 0 ;
 for ( p = _tags ;
 ;
 p = q ) {
 while ( * p == ' ' ) p ++ ;
 if ( p [ 0 ] == '\0' ) break ;
 for ( q = p + 1 ;
 * q != '\0' && * q != ' ' ;
 q ++ ) ;
 switch ( p [ 0 ] ) {
 case 'W' : {
 if ( sscanf ( p + 1 , "%d" , & _y4m -> pic_w ) != 1 ) return - 1 ;
 got_w = 1 ;
 }
 break ;
 case 'H' : {
 if ( sscanf ( p + 1 , "%d" , & _y4m -> pic_h ) != 1 ) return - 1 ;
 got_h = 1 ;
 }
 break ;
 case 'F' : {
 if ( sscanf ( p + 1 , "%d:%d" , & _y4m -> fps_n , & _y4m -> fps_d ) != 2 ) {
 return - 1 ;
 }
 got_fps = 1 ;
 }
 break ;
 case 'I' : {
 _y4m -> interlace = p [ 1 ] ;
 got_interlace = 1 ;
 }
 break ;
 case 'A' : {
 if ( sscanf ( p + 1 , "%d:%d" , & _y4m -> par_n , & _y4m -> par_d ) != 2 ) {
 return - 1 ;
 }
 got_par = 1 ;
 }
 break ;
 case 'C' : {
 if ( q - p > 16 ) return - 1 ;
 memcpy ( _y4m -> chroma_type , p + 1 , q - p - 1 ) ;
 _y4m -> chroma_type [ q - p - 1 ] = '\0' ;
 got_chroma = 1 ;
 }
 break ;
 }
 }
 if ( ! got_w || ! got_h || ! got_fps ) return - 1 ;
 if ( ! got_interlace ) _y4m -> interlace = '?' ;
 if ( ! got_par ) _y4m -> par_n = _y4m -> par_d = 0 ;
 if ( ! got_chroma ) strcpy ( _y4m -> chroma_type , "420" ) ;
 return 0 ;
 }