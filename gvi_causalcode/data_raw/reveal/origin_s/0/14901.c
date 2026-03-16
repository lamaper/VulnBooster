void qemuAgentClose ( qemuAgentPtr mon ) {
 if ( ! mon ) return ;
 VIR_DEBUG ( "mon=%p" , mon ) ;
 virObjectLock ( mon ) ;
 if ( mon -> fd >= 0 ) {
 if ( mon -> watch ) virEventRemoveHandle ( mon -> watch ) ;
 VIR_FORCE_CLOSE ( mon -> fd ) ;
 }
 qemuAgentNotifyCloseLocked ( mon ) ;
 virObjectUnlock ( mon ) ;
 virObjectUnref ( mon ) ;
 }