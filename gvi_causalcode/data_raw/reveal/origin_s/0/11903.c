static inline void qemu_put_be64s ( QEMUFile * f , const uint64_t * pv ) {
 qemu_put_be64 ( f , * pv ) ;
 }