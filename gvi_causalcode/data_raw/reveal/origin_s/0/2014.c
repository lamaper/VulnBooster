const char * qemuAliasDiskDriveSkipPrefix ( const char * dev_name ) {
 if ( STRPREFIX ( dev_name , QEMU_DRIVE_HOST_PREFIX ) ) dev_name += strlen ( QEMU_DRIVE_HOST_PREFIX ) ;
 return dev_name ;
 }