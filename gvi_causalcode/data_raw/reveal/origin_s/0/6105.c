static bool tsc_khz_needed ( void * opaque ) {
 X86CPU * cpu = opaque ;
 CPUX86State * env = & cpu -> env ;
 MachineClass * mc = MACHINE_GET_CLASS ( qdev_get_machine ( ) ) ;
 PCMachineClass * pcmc = PC_MACHINE_CLASS ( mc ) ;
 return env -> tsc_khz && pcmc -> save_tsc_khz ;
 }