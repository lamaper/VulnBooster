static int set_property ( const char * name , const char * value , void * opaque ) {
 DeviceState * dev = opaque ;
 if ( strcmp ( name , "driver" ) == 0 ) return 0 ;
 if ( strcmp ( name , "bus" ) == 0 ) return 0 ;
 if ( qdev_prop_parse ( dev , name , value ) == - 1 ) {
 qemu_error ( "can't set property \"%s\" to \"%s\" for \"%s\"\n" , name , value , dev -> info -> name ) ;
 return - 1 ;
 }
 return 0 ;
 }