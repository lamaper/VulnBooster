int qemuMonitorTextGetVirtType ( qemuMonitorPtr mon , int * virtType ) {
 char * reply = NULL ;
 * virtType = VIR_DOMAIN_VIRT_QEMU ;
 if ( qemuMonitorHMPCommand ( mon , "info kvm" , & reply ) < 0 ) {
 qemuReportError ( VIR_ERR_OPERATION_FAILED , "%s" , _ ( "could not query kvm status" ) ) ;
 return - 1 ;
 }
 if ( strstr ( reply , "enabled" ) ) * virtType = VIR_DOMAIN_VIRT_KVM ;
 VIR_FREE ( reply ) ;
 return 0 ;
 }