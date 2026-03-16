void cpu_resume ( CPUState * cpu ) {
 cpu -> stop = false ;
 cpu -> stopped = false ;
 qemu_cpu_kick ( cpu ) ;
 }