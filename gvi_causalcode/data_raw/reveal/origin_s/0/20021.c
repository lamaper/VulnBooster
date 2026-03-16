void vmport_register ( unsigned char command , VMPortReadFunc * func , void * opaque ) {
 if ( command >= VMPORT_ENTRIES ) return ;
 port_state -> func [ command ] = func ;
 port_state -> opaque [ command ] = opaque ;
 }