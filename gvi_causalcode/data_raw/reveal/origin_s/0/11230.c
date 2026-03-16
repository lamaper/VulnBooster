static int cpu_pre_save ( void * opaque ) {
 X86CPU * cpu = opaque ;
 CPUX86State * env = & cpu -> env ;
 int i ;
 env -> fpus_vmstate = ( env -> fpus & ~ 0x3800 ) | ( env -> fpstt & 0x7 ) << 11 ;
 env -> fptag_vmstate = 0 ;
 for ( i = 0 ;
 i < 8 ;
 i ++ ) {
 env -> fptag_vmstate |= ( ( ! env -> fptags [ i ] ) << i ) ;
 }
 env -> fpregs_format_vmstate = 0 ;
 if ( ! ( env -> cr [ 0 ] & CR0_PE_MASK ) && ( env -> segs [ R_CS ] . flags >> DESC_DPL_SHIFT & 3 ) != 0 ) {
 env -> segs [ R_CS ] . flags &= ~ ( env -> segs [ R_CS ] . flags & DESC_DPL_MASK ) ;
 env -> segs [ R_DS ] . flags &= ~ ( env -> segs [ R_DS ] . flags & DESC_DPL_MASK ) ;
 env -> segs [ R_ES ] . flags &= ~ ( env -> segs [ R_ES ] . flags & DESC_DPL_MASK ) ;
 env -> segs [ R_FS ] . flags &= ~ ( env -> segs [ R_FS ] . flags & DESC_DPL_MASK ) ;
 env -> segs [ R_GS ] . flags &= ~ ( env -> segs [ R_GS ] . flags & DESC_DPL_MASK ) ;
 env -> segs [ R_SS ] . flags &= ~ ( env -> segs [ R_SS ] . flags & DESC_DPL_MASK ) ;
 }
 return 0 ;
 }