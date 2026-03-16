static int __app_register_atfork ( void ( * prepare ) ( void ) , void ( * parent ) ( void ) , void ( * child ) ( void ) ) {
 return __register_atfork ( prepare , parent , child , & __dso_handle == NULL ? NULL : __dso_handle ) ;
 }