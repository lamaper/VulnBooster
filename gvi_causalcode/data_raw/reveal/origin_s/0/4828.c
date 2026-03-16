static int get_filter_offset ( const int16_t * f , const InterpKernel * base ) {
 return ( int ) ( ( const InterpKernel * ) ( intptr_t ) f - base ) ;
 }