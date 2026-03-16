static int qdev_print_devinfo ( DeviceInfo * info , char * dest , int len ) {
 int pos = 0 ;
 int ret ;
 ret = snprintf ( dest + pos , len - pos , "name \"%s\", bus %s" , info -> name , info -> bus_info -> name ) ;
 pos += MIN ( len - pos , ret ) ;
 if ( info -> alias ) {
 ret = snprintf ( dest + pos , len - pos , ", alias \"%s\"" , info -> alias ) ;
 pos += MIN ( len - pos , ret ) ;
 }
 if ( info -> desc ) {
 ret = snprintf ( dest + pos , len - pos , ", desc \"%s\"" , info -> desc ) ;
 pos += MIN ( len - pos , ret ) ;
 }
 if ( info -> no_user ) {
 ret = snprintf ( dest + pos , len - pos , ", no-user" ) ;
 pos += MIN ( len - pos , ret ) ;
 }
 return pos ;
 }