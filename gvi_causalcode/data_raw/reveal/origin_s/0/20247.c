static inline uint64_t e1000e_ring_base ( E1000ECore * core , const E1000E_RingInfo * r ) {
 uint64_t bah = core -> mac [ r -> dbah ] ;
 uint64_t bal = core -> mac [ r -> dbal ] ;
 return ( bah << 32 ) + bal ;
 }