static void prom_init ( hwaddr addr , const char * bios_name ) {
 DeviceState * dev ;
 SysBusDevice * s ;
 char * filename ;
 int ret ;
 dev = qdev_create ( NULL , "openprom" ) ;
 qdev_init_nofail ( dev ) ;
 s = SYS_BUS_DEVICE ( dev ) ;
 sysbus_mmio_map ( s , 0 , addr ) ;
 if ( bios_name == NULL ) {
 bios_name = PROM_FILENAME ;
 }
 filename = qemu_find_file ( QEMU_FILE_TYPE_BIOS , bios_name ) ;
 if ( filename ) {
 ret = load_elf ( filename , translate_prom_address , & addr , NULL , NULL , NULL , 1 , ELF_MACHINE , 0 ) ;
 if ( ret < 0 || ret > PROM_SIZE_MAX ) {
 ret = load_image_targphys ( filename , addr , PROM_SIZE_MAX ) ;
 }
 g_free ( filename ) ;
 }
 else {
 ret = - 1 ;
 }
 if ( ret < 0 || ret > PROM_SIZE_MAX ) {
 fprintf ( stderr , "qemu: could not load prom '%s'\n" , bios_name ) ;
 exit ( 1 ) ;
 }
 }