static const InterpKernel * get_filter_base ( const int16_t * filter ) {
 return ( const InterpKernel * ) ( ( ( intptr_t ) filter ) & ~ ( ( intptr_t ) 0xFF ) ) ;
 }