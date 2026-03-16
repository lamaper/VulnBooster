static int qemuMonitorJSONGetMigrationStatusReply ( virJSONValuePtr reply , int * status , unsigned long long * transferred , unsigned long long * remaining , unsigned long long * total ) {
 virJSONValuePtr ret ;
 const char * statusstr ;
 unsigned long long t ;
 if ( ! ( ret = virJSONValueObjectGet ( reply , "return" ) ) ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "info migration reply was missing return data" ) ) ;
 return - 1 ;
 }
 if ( ! ( statusstr = virJSONValueObjectGetString ( ret , "status" ) ) ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "info migration reply was missing return status" ) ) ;
 return - 1 ;
 }
 if ( ( * status = qemuMonitorMigrationStatusTypeFromString ( statusstr ) ) < 0 ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , _ ( "unexpected migration status in %s" ) , statusstr ) ;
 return - 1 ;
 }
 if ( * status == QEMU_MONITOR_MIGRATION_STATUS_ACTIVE ) {
 virJSONValuePtr ram = virJSONValueObjectGet ( ret , "ram" ) ;
 if ( ! ram ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "migration was active, but no RAM info was set" ) ) ;
 return - 1 ;
 }
 if ( virJSONValueObjectGetNumberUlong ( ram , "transferred" , transferred ) < 0 ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "migration was active, but RAM 'transferred' " "data was missing" ) ) ;
 return - 1 ;
 }
 if ( virJSONValueObjectGetNumberUlong ( ram , "remaining" , remaining ) < 0 ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "migration was active, but RAM 'remaining' " "data was missing" ) ) ;
 return - 1 ;
 }
 if ( virJSONValueObjectGetNumberUlong ( ram , "total" , total ) < 0 ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "migration was active, but RAM 'total' " "data was missing" ) ) ;
 return - 1 ;
 }
 virJSONValuePtr disk = virJSONValueObjectGet ( ret , "disk" ) ;
 if ( ! disk ) {
 return 0 ;
 }
 if ( virJSONValueObjectGetNumberUlong ( disk , "transferred" , & t ) < 0 ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "disk migration was active, but 'transferred' " "data was missing" ) ) ;
 return - 1 ;
 }
 * transferred += t ;
 if ( virJSONValueObjectGetNumberUlong ( disk , "remaining" , & t ) < 0 ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "disk migration was active, but 'remaining' " "data was missing" ) ) ;
 return - 1 ;
 }
 * remaining += t ;
 if ( virJSONValueObjectGetNumberUlong ( disk , "total" , & t ) < 0 ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "disk migration was active, but 'total' " "data was missing" ) ) ;
 return - 1 ;
 }
 * total += t ;
 }
 return 0 ;
 }