static void nvic_writel ( nvic_state * s , uint32_t offset , uint32_t value ) {
 uint32_t oldval ;
 switch ( offset ) {
 case 0x10 : oldval = s -> systick . control ;
 s -> systick . control &= 0xfffffff8 ;
 s -> systick . control |= value & 7 ;
 if ( ( oldval ^ value ) & SYSTICK_ENABLE ) {
 int64_t now = qemu_get_clock_ns ( vm_clock ) ;
 if ( value & SYSTICK_ENABLE ) {
 if ( s -> systick . tick ) {
 s -> systick . tick += now ;
 qemu_mod_timer ( s -> systick . timer , s -> systick . tick ) ;
 }
 else {
 systick_reload ( s , 1 ) ;
 }
 }
 else {
 qemu_del_timer ( s -> systick . timer ) ;
 s -> systick . tick -= now ;
 if ( s -> systick . tick < 0 ) s -> systick . tick = 0 ;
 }
 }
 else if ( ( oldval ^ value ) & SYSTICK_CLKSOURCE ) {
 systick_reload ( s , 1 ) ;
 }
 break ;
 case 0x14 : s -> systick . reload = value ;
 break ;
 case 0x18 : systick_reload ( s , 1 ) ;
 s -> systick . control &= ~ SYSTICK_COUNTFLAG ;
 break ;
 case 0xd04 : if ( value & ( 1 << 31 ) ) {
 armv7m_nvic_set_pending ( s , ARMV7M_EXCP_NMI ) ;
 }
 if ( value & ( 1 << 28 ) ) {
 armv7m_nvic_set_pending ( s , ARMV7M_EXCP_PENDSV ) ;
 }
 else if ( value & ( 1 << 27 ) ) {
 s -> gic . irq_state [ ARMV7M_EXCP_PENDSV ] . pending = 0 ;
 gic_update ( & s -> gic ) ;
 }
 if ( value & ( 1 << 26 ) ) {
 armv7m_nvic_set_pending ( s , ARMV7M_EXCP_SYSTICK ) ;
 }
 else if ( value & ( 1 << 25 ) ) {
 s -> gic . irq_state [ ARMV7M_EXCP_SYSTICK ] . pending = 0 ;
 gic_update ( & s -> gic ) ;
 }
 break ;
 case 0xd08 : cpu_single_env -> v7m . vecbase = value & 0xffffff80 ;
 break ;
 case 0xd0c : if ( ( value >> 16 ) == 0x05fa ) {
 if ( value & 2 ) {
 qemu_log_mask ( LOG_UNIMP , "VECTCLRACTIVE unimplemented\n" ) ;
 }
 if ( value & 5 ) {
 qemu_log_mask ( LOG_UNIMP , "AIRCR system reset unimplemented\n" ) ;
 }
 }
 break ;
 case 0xd10 : case 0xd14 : qemu_log_mask ( LOG_UNIMP , "NVIC: SCR and CCR unimplemented\n" ) ;
 break ;
 case 0xd24 : s -> gic . irq_state [ ARMV7M_EXCP_MEM ] . enabled = ( value & ( 1 << 16 ) ) != 0 ;
 s -> gic . irq_state [ ARMV7M_EXCP_BUS ] . enabled = ( value & ( 1 << 17 ) ) != 0 ;
 s -> gic . irq_state [ ARMV7M_EXCP_USAGE ] . enabled = ( value & ( 1 << 18 ) ) != 0 ;
 break ;
 case 0xd28 : case 0xd2c : case 0xd30 : case 0xd34 : case 0xd38 : case 0xd3c : qemu_log_mask ( LOG_UNIMP , "NVIC: fault status registers unimplemented\n" ) ;
 break ;
 case 0xf00 : if ( ( value & 0x1ff ) < s -> num_irq ) {
 gic_set_pending_private ( & s -> gic , 0 , value & 0x1ff ) ;
 }
 break ;
 default : qemu_log_mask ( LOG_GUEST_ERROR , "NVIC: Bad write offset 0x%x\n" , offset ) ;
 }
 }