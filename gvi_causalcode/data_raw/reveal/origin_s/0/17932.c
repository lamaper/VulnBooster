static inline target_phys_addr_t vring_align ( target_phys_addr_t addr , unsigned long align ) {
 return ( addr + align - 1 ) & ~ ( align - 1 ) ;
 }