int vp9_set_size_literal ( VP9_COMP * cpi , unsigned int width , unsigned int height ) {
 VP9_COMMON * cm = & cpi -> common ;
 check_initial_width ( cpi , 1 , 1 ) ;
 if ( width ) {
 cm -> width = width ;
 if ( cm -> width * 5 < cpi -> initial_width ) {
 cm -> width = cpi -> initial_width / 5 + 1 ;
 printf ( "Warning: Desired width too small, changed to %d\n" , cm -> width ) ;
 }
 if ( cm -> width > cpi -> initial_width ) {
 cm -> width = cpi -> initial_width ;
 printf ( "Warning: Desired width too large, changed to %d\n" , cm -> width ) ;
 }
 }
 if ( height ) {
 cm -> height = height ;
 if ( cm -> height * 5 < cpi -> initial_height ) {
 cm -> height = cpi -> initial_height / 5 + 1 ;
 printf ( "Warning: Desired height too small, changed to %d\n" , cm -> height ) ;
 }
 if ( cm -> height > cpi -> initial_height ) {
 cm -> height = cpi -> initial_height ;
 printf ( "Warning: Desired height too large, changed to %d\n" , cm -> height ) ;
 }
 }
 assert ( cm -> width <= cpi -> initial_width ) ;
 assert ( cm -> height <= cpi -> initial_height ) ;
 update_frame_size ( cpi ) ;
 return 0 ;
 }