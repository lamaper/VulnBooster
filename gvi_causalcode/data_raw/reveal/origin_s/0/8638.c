static void cin_apply_delta_data ( const unsigned char * src , unsigned char * dst , int size ) {
 while ( size -- ) * dst ++ += * src ++ ;
 }