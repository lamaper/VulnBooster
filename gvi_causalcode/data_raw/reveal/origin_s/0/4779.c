static void vmport_realizefn ( DeviceState * dev , Error * * errp ) {
 ISADevice * isadev = ISA_DEVICE ( dev ) ;
 VMPortState * s = VMPORT ( dev ) ;
 memory_region_init_io ( & s -> io , OBJECT ( s ) , & vmport_ops , s , "vmport" , 1 ) ;
 isa_register_ioport ( isadev , & s -> io , 0x5658 ) ;
 port_state = s ;
 vmport_register ( VMPORT_CMD_GETVERSION , vmport_cmd_get_version , NULL ) ;
 vmport_register ( VMPORT_CMD_GETRAMSIZE , vmport_cmd_ram_size , NULL ) ;
 }