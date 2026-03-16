static bool tsc_is_stable_and_known ( CPUX86State * env ) {
 if ( ! env -> tsc_khz ) {
 return false ;
 }
 return ( env -> features [ FEAT_8000_0007_EDX ] & CPUID_APM_INVTSC ) || env -> user_tsc_khz ;
 }