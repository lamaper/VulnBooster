int qemuMonitorTextGetMigrationStatus ( qemuMonitorPtr mon , int * status , unsigned long long * transferred , unsigned long long * remaining , unsigned long long * total ) {
 char * reply ;
 char * tmp ;
 char * end ;
 unsigned long long disk_transferred = 0 ;
 unsigned long long disk_remaining = 0 ;
 unsigned long long disk_total = 0 ;
 int ret = - 1 ;
 * status = QEMU_MONITOR_MIGRATION_STATUS_INACTIVE ;
 * transferred = 0 ;
 * remaining = 0 ;
 * total = 0 ;
 if ( qemuMonitorHMPCommand ( mon , "info migrate" , & reply ) < 0 ) {
 qemuReportError ( VIR_ERR_OPERATION_FAILED , "%s" , _ ( "cannot query migration status" ) ) ;
 return - 1 ;
 }
 if ( ( tmp = strstr ( reply , MIGRATION_PREFIX ) ) != NULL ) {
 tmp += strlen ( MIGRATION_PREFIX ) ;
 end = strchr ( tmp , '\r' ) ;
 if ( end == NULL ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , _ ( "unexpected migration status in %s" ) , reply ) ;
 goto cleanup ;
 }
 * end = '\0' ;
 if ( ( * status = qemuMonitorMigrationStatusTypeFromString ( tmp ) ) < 0 ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , _ ( "unexpected migration status in %s" ) , reply ) ;
 goto cleanup ;
 }
 if ( * status == QEMU_MONITOR_MIGRATION_STATUS_ACTIVE ) {
 tmp = end + 1 ;
 if ( ! ( tmp = strstr ( tmp , MIGRATION_TRANSFER_PREFIX ) ) ) goto done ;
 tmp += strlen ( MIGRATION_TRANSFER_PREFIX ) ;
 if ( virStrToLong_ull ( tmp , & end , 10 , transferred ) < 0 ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , _ ( "cannot parse migration data transferred " "statistic %s" ) , tmp ) ;
 goto cleanup ;
 }
 * transferred *= 1024 ;
 tmp = end ;
 if ( ! ( tmp = strstr ( tmp , MIGRATION_REMAINING_PREFIX ) ) ) goto done ;
 tmp += strlen ( MIGRATION_REMAINING_PREFIX ) ;
 if ( virStrToLong_ull ( tmp , & end , 10 , remaining ) < 0 ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , _ ( "cannot parse migration data remaining " "statistic %s" ) , tmp ) ;
 goto cleanup ;
 }
 * remaining *= 1024 ;
 tmp = end ;
 if ( ! ( tmp = strstr ( tmp , MIGRATION_TOTAL_PREFIX ) ) ) goto done ;
 tmp += strlen ( MIGRATION_TOTAL_PREFIX ) ;
 if ( virStrToLong_ull ( tmp , & end , 10 , total ) < 0 ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , _ ( "cannot parse migration data total " "statistic %s" ) , tmp ) ;
 goto cleanup ;
 }
 * total *= 1024 ;
 tmp = end ;
 if ( ! ( tmp = strstr ( tmp , MIGRATION_DISK_TRANSFER_PREFIX ) ) ) goto done ;
 tmp += strlen ( MIGRATION_DISK_TRANSFER_PREFIX ) ;
 if ( virStrToLong_ull ( tmp , & end , 10 , & disk_transferred ) < 0 ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , _ ( "cannot parse disk migration data " "transferred statistic %s" ) , tmp ) ;
 goto cleanup ;
 }
 * transferred += disk_transferred * 1024 ;
 tmp = end ;
 if ( ! ( tmp = strstr ( tmp , MIGRATION_DISK_REMAINING_PREFIX ) ) ) goto done ;
 tmp += strlen ( MIGRATION_DISK_REMAINING_PREFIX ) ;
 if ( virStrToLong_ull ( tmp , & end , 10 , & disk_remaining ) < 0 ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , _ ( "cannot parse disk migration data remaining " "statistic %s" ) , tmp ) ;
 goto cleanup ;
 }
 * remaining += disk_remaining * 1024 ;
 tmp = end ;
 if ( ! ( tmp = strstr ( tmp , MIGRATION_DISK_TOTAL_PREFIX ) ) ) goto done ;
 tmp += strlen ( MIGRATION_DISK_TOTAL_PREFIX ) ;
 if ( virStrToLong_ull ( tmp , & end , 10 , & disk_total ) < 0 ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , _ ( "cannot parse disk migration data total " "statistic %s" ) , tmp ) ;
 goto cleanup ;
 }
 * total += disk_total * 1024 ;
 }
 }
 done : ret = 0 ;
 cleanup : VIR_FREE ( reply ) ;
 return ret ;
 }