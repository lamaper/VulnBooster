static void Pass1Encode ( VP8_COMP * cpi , unsigned long * size , unsigned char * dest , unsigned int * frame_flags ) {
 ( void ) size ;
 ( void ) dest ;
 ( void ) frame_flags ;
 vp8_set_quantizer ( cpi , 26 ) ;
 vp8_first_pass ( cpi ) ;
 }