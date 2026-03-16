void qemuAgentNotifyClose ( qemuAgentPtr mon ) {
 if ( ! mon ) return ;
 VIR_DEBUG ( "mon=%p" , mon ) ;
 virObjectLock ( mon ) ;
 qemuAgentNotifyCloseLocked ( mon ) ;
 virObjectUnlock ( mon ) ;
 }