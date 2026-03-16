static int qemuMonitorJSONGetGuestDriveAddress ( virJSONValuePtr reply , virDomainDeviceDriveAddress * driveAddr ) {
 virJSONValuePtr addr ;
 addr = virJSONValueObjectGet ( reply , "return" ) ;
 if ( ! addr || addr -> type != VIR_JSON_TYPE_OBJECT ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "drive_add reply was missing device address" ) ) ;
 return - 1 ;
 }
 if ( virJSONValueObjectGetNumberUint ( addr , "bus" , & driveAddr -> bus ) < 0 ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "drive_add reply was missing device bus number" ) ) ;
 return - 1 ;
 }
 if ( virJSONValueObjectGetNumberUint ( addr , "unit" , & driveAddr -> unit ) < 0 ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "drive_add reply was missing device unit number" ) ) ;
 return - 1 ;
 }
 return 0 ;
 }