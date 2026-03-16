static int cpu_post_load ( void * opaque , int version_id ) {
 X86CPU * cpu = opaque ;
 CPUState * cs = CPU ( cpu ) ;
 CPUX86State * env = & cpu -> env ;
 int i ;
 if ( env -> tsc_khz && env -> user_tsc_khz && env -> tsc_khz != env -> user_tsc_khz ) {
 error_report ( "Mismatch between user-specified TSC frequency and " "migrated TSC frequency" ) ;
 return - EINVAL ;
 }
 if ( env -> fpregs_format_vmstate ) {
 error_report ( "Unsupported old non-softfloat CPU state" ) ;
 return - EINVAL ;
 }
 if ( ! ( env -> cr [ 0 ] & CR0_PE_MASK ) && ( env -> segs [ R_CS ] . flags >> DESC_DPL_SHIFT & 3 ) != 0 ) {
 env -> segs [ R_CS ] . flags &= ~ ( env -> segs [ R_CS ] . flags & DESC_DPL_MASK ) ;
 env -> segs [ R_DS ] . flags &= ~ ( env -> segs [ R_DS ] . flags & DESC_DPL_MASK ) ;
 env -> segs [ R_ES ] . flags &= ~ ( env -> segs [ R_ES ] . flags & DESC_DPL_MASK ) ;
 env -> segs [ R_FS ] . flags &= ~ ( env -> segs [ R_FS ] . flags & DESC_DPL_MASK ) ;
 env -> segs [ R_GS ] . flags &= ~ ( env -> segs [ R_GS ] . flags & DESC_DPL_MASK ) ;
 env -> segs [ R_SS ] . flags &= ~ ( env -> segs [ R_SS ] . flags & DESC_DPL_MASK ) ;
 }
 env -> hflags &= ~ HF_CPL_MASK ;
 env -> hflags |= ( env -> segs [ R_SS ] . flags >> DESC_DPL_SHIFT ) & HF_CPL_MASK ;
 env -> fpstt = ( env -> fpus_vmstate >> 11 ) & 7 ;
 env -> fpus = env -> fpus_vmstate & ~ 0x3800 ;
 env -> fptag_vmstate ^= 0xff ;
 for ( i = 0 ;
 i < 8 ;
 i ++ ) {
 env -> fptags [ i ] = ( env -> fptag_vmstate >> i ) & 1 ;
 }
 if ( tcg_enabled ( ) ) {
 target_ulong dr7 ;
 update_fp_status ( env ) ;
 update_mxcsr_status ( env ) ;
 cpu_breakpoint_remove_all ( cs , BP_CPU ) ;
 cpu_watchpoint_remove_all ( cs , BP_CPU ) ;
 dr7 = env -> dr [ 7 ] ;
 env -> dr [ 7 ] = dr7 & ~ ( DR7_GLOBAL_BP_MASK | DR7_LOCAL_BP_MASK ) ;
 cpu_x86_update_dr7 ( env , dr7 ) ;
 }
 tlb_flush ( cs ) ;
 return 0 ;
 }