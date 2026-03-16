int gdev_x_get_params ( gx_device * dev , gs_param_list * plist ) {
 gx_device_X * xdev = ( gx_device_X * ) dev ;
 int code = gx_default_get_params ( dev , plist ) ;
 long id = ( long ) xdev -> pwin ;
 if ( code < 0 || ( code = param_write_long ( plist , "WindowID" , & id ) ) < 0 || ( code = param_write_bool ( plist , ".IsPageDevice" , & xdev -> IsPageDevice ) ) < 0 || ( code = param_write_int ( plist , "MaxTempPixmap" , & xdev -> MaxTempPixmap ) ) < 0 || ( code = param_write_int ( plist , "MaxTempImage" , & xdev -> MaxTempImage ) ) < 0 ) DO_NOTHING ;
 return code ;
 }