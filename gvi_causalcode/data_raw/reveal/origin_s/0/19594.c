static void ppc_prep_reset ( void * opaque ) {
 PowerPCCPU * cpu = opaque ;
 cpu_reset ( CPU ( cpu ) ) ;
 cpu -> env . nip = 0xfffffffc ;
 }