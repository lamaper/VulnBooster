static int pxa2xx_clkcfg_read ( CPUARMState * env , const ARMCPRegInfo * ri , uint64_t * value ) {
 PXA2xxState * s = ( PXA2xxState * ) ri -> opaque ;
 * value = s -> clkcfg ;
 return 0 ;
 }