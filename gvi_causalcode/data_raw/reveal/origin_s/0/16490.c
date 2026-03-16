void generate_filename ( const char * pattern , char * out , size_t q_len , unsigned int d_w , unsigned int d_h , unsigned int frame_in ) {
 const char * p = pattern ;
 char * q = out ;
 do {
 char * next_pat = strchr ( p , '%' ) ;
 if ( p == next_pat ) {
 size_t pat_len ;
 q [ q_len - 1 ] = '\0' ;
 switch ( p [ 1 ] ) {
 case 'w' : snprintf ( q , q_len - 1 , "%d" , d_w ) ;
 break ;
 case 'h' : snprintf ( q , q_len - 1 , "%d" , d_h ) ;
 break ;
 case '1' : snprintf ( q , q_len - 1 , "%d" , frame_in ) ;
 break ;
 case '2' : snprintf ( q , q_len - 1 , "%02d" , frame_in ) ;
 break ;
 case '3' : snprintf ( q , q_len - 1 , "%03d" , frame_in ) ;
 break ;
 case '4' : snprintf ( q , q_len - 1 , "%04d" , frame_in ) ;
 break ;
 case '5' : snprintf ( q , q_len - 1 , "%05d" , frame_in ) ;
 break ;
 case '6' : snprintf ( q , q_len - 1 , "%06d" , frame_in ) ;
 break ;
 case '7' : snprintf ( q , q_len - 1 , "%07d" , frame_in ) ;
 break ;
 case '8' : snprintf ( q , q_len - 1 , "%08d" , frame_in ) ;
 break ;
 case '9' : snprintf ( q , q_len - 1 , "%09d" , frame_in ) ;
 break ;
 default : die ( "Unrecognized pattern %%%c\n" , p [ 1 ] ) ;
 break ;
 }
 pat_len = strlen ( q ) ;
 if ( pat_len >= q_len - 1 ) die ( "Output filename too long.\n" ) ;
 q += pat_len ;
 p += 2 ;
 q_len -= pat_len ;
 }
 else {
 size_t copy_len ;
 if ( ! next_pat ) copy_len = strlen ( p ) ;
 else copy_len = next_pat - p ;
 if ( copy_len >= q_len - 1 ) die ( "Output filename too long.\n" ) ;
 memcpy ( q , p , copy_len ) ;
 q [ copy_len ] = '\0' ;
 q += copy_len ;
 p += copy_len ;
 q_len -= copy_len ;
 }
 }
 while ( * p ) ;
 }