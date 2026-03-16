static void kvm_mce_inject ( X86CPU * cpu , hwaddr paddr , int code ) {
 CPUState * cs = CPU ( cpu ) ;
 CPUX86State * env = & cpu -> env ;
 uint64_t status = MCI_STATUS_VAL | MCI_STATUS_UC | MCI_STATUS_EN | MCI_STATUS_MISCV | MCI_STATUS_ADDRV | MCI_STATUS_S ;
 uint64_t mcg_status = MCG_STATUS_MCIP ;
 int flags = 0 ;
 if ( code == BUS_MCEERR_AR ) {
 status |= MCI_STATUS_AR | 0x134 ;
 mcg_status |= MCG_STATUS_EIPV ;
 }
 else {
 status |= 0xc0 ;
 mcg_status |= MCG_STATUS_RIPV ;
 }
 flags = cpu_x86_support_mca_broadcast ( env ) ? MCE_INJECT_BROADCAST : 0 ;
 cpu_synchronize_state ( cs ) ;
 if ( env -> mcg_ext_ctl & MCG_EXT_CTL_LMCE_EN ) {
 mcg_status |= MCG_STATUS_LMCE ;
 flags = 0 ;
 }
 cpu_x86_inject_mce ( NULL , cpu , 9 , status , mcg_status , paddr , ( MCM_ADDR_PHYS << 6 ) | 0xc , flags ) ;
 }