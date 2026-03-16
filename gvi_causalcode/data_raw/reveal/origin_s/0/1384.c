static int pxa2xx_cpccnt_read ( CPUARMState * env , const ARMCPRegInfo * ri , uint64_t * value ) {
 PXA2xxState * s = ( PXA2xxState * ) ri -> opaque ;
 if ( s -> pmnc & 1 ) {
 * value = qemu_get_clock_ns ( vm_clock ) ;
 }
 else {
 * value = 0 ;
 }
 return 0 ;
 }