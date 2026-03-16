BlockDriverState * qdev_init_bdrv ( DeviceState * dev , BlockInterfaceType type ) {
 int unit = next_block_unit [ type ] ++ ;
 DriveInfo * dinfo ;
 dinfo = drive_get ( type , 0 , unit ) ;
 return dinfo ? dinfo -> bdrv : NULL ;
 }