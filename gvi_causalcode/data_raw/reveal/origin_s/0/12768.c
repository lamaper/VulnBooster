static inline void e1000e_rx_ring_init ( E1000ECore * core , E1000E_RxRing * rxr , int idx ) {
 static const E1000E_RingInfo i [ E1000E_NUM_QUEUES ] = {
 {
 RDBAH0 , RDBAL0 , RDLEN0 , RDH0 , RDT0 , 0 }
 , {
 RDBAH1 , RDBAL1 , RDLEN1 , RDH1 , RDT1 , 1 }
 }
 ;
 assert ( idx < ARRAY_SIZE ( i ) ) ;
 rxr -> i = & i [ idx ] ;
 }