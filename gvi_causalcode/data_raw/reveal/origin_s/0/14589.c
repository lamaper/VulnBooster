void vapic_report_tpr_access ( DeviceState * dev , CPUState * cs , target_ulong ip , TPRAccess access ) {
 VAPICROMState * s = DO_UPCAST ( VAPICROMState , busdev . qdev , dev ) ;
 X86CPU * cpu = X86_CPU ( cs ) ;
 CPUX86State * env = & cpu -> env ;
 cpu_synchronize_state ( cs ) ;
 if ( evaluate_tpr_instruction ( s , env , & ip , access ) < 0 ) {
 if ( s -> state == VAPIC_ACTIVE ) {
 vapic_enable ( s , env ) ;
 }
 return ;
 }
 if ( update_rom_mapping ( s , env , ip ) < 0 ) {
 return ;
 }
 if ( vapic_enable ( s , env ) < 0 ) {
 return ;
 }
 patch_instruction ( s , cpu , ip ) ;
 }