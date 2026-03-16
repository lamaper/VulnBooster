static PageDesc * page_find_alloc ( tb_page_addr_t index , int alloc ) {
 PageDesc * pd ;
 void * * lp ;
 int i ;

 P = mmap ( NULL , SIZE , PROT_READ | PROT_WRITE , MAP_PRIVATE | MAP_ANONYMOUS , - 1 , 0 ) ;
 }
 while ( 0 ) # else # define ALLOC ( P , SIZE ) do {
 P = g_malloc0 ( SIZE ) ;
 }
 while ( 0 ) # endif lp = l1_map + ( ( index >> V_L1_SHIFT ) & ( V_L1_SIZE - 1 ) ) ;
 for ( i = V_L1_SHIFT / L2_BITS - 1 ;
 i > 0 ;
 i -- ) {
 void * * p = * lp ;
 if ( p == NULL ) {
 if ( ! alloc ) {
 return NULL ;
 }
 ALLOC ( p , sizeof ( void * ) * L2_SIZE ) ;
 * lp = p ;
 }
 lp = p + ( ( index >> ( i * L2_BITS ) ) & ( L2_SIZE - 1 ) ) ;
 }
 pd = * lp ;
 if ( pd == NULL ) {
 if ( ! alloc ) {
 return NULL ;
 }
 ALLOC ( pd , sizeof ( PageDesc ) * L2_SIZE ) ;
 * lp = pd ;
 }

 }