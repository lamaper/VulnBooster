int qemuMonitorTextSendKey ( qemuMonitorPtr mon , unsigned int holdtime , unsigned int * keycodes , unsigned int nkeycodes ) {
 int i ;
 virBuffer buf = VIR_BUFFER_INITIALIZER ;
 char * cmd , * reply = NULL ;
 int ret = - 1 ;
 if ( nkeycodes > VIR_DOMAIN_SEND_KEY_MAX_KEYS || nkeycodes == 0 ) return - 1 ;
 virBufferAddLit ( & buf , "sendkey " ) ;
 for ( i = 0 ;
 i < nkeycodes ;
 i ++ ) {
 if ( keycodes [ i ] > 0xffff ) {
 qemuReportError ( VIR_ERR_OPERATION_FAILED , _ ( "keycode %d is invalid: 0x%X" ) , i , keycodes [ i ] ) ;
 virBufferFreeAndReset ( & buf ) ;
 return - 1 ;
 }
 if ( i ) virBufferAddChar ( & buf , '-' ) ;
 virBufferAsprintf ( & buf , "0x%02X" , keycodes [ i ] ) ;
 }
 if ( holdtime ) virBufferAsprintf ( & buf , " %u" , holdtime ) ;
 if ( virBufferError ( & buf ) ) {
 virReportOOMError ( ) ;
 return - 1 ;
 }
 cmd = virBufferContentAndReset ( & buf ) ;
 if ( qemuMonitorHMPCommand ( mon , cmd , & reply ) < 0 ) {
 qemuReportError ( VIR_ERR_OPERATION_FAILED , _ ( "failed to send key using command '%s'" ) , cmd ) ;
 goto cleanup ;
 }
 if ( STRNEQ ( reply , "" ) ) {
 qemuReportError ( VIR_ERR_OPERATION_FAILED , _ ( "failed to send key '%s'" ) , reply ) ;
 goto cleanup ;
 }
 ret = 0 ;
 cleanup : VIR_FREE ( cmd ) ;
 VIR_FREE ( reply ) ;
 return ret ;
 }