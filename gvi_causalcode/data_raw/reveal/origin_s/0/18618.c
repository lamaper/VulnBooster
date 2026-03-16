static void openpic_summary_write ( void * opaque , hwaddr addr , uint64_t val , unsigned size ) {
 DPRINTF ( "%s: addr %#" HWADDR_PRIx " <= 0x%08" PRIx64 "\n" , __func__ , addr , val ) ;
 }