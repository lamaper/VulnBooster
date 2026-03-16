void linux_udev_hotplug_poll ( void ) {
 struct udev_device * udev_dev ;
 usbi_mutex_static_lock ( & linux_hotplug_lock ) ;
 do {
 udev_dev = device : : udev_monitor_receive_device ( udev_monitor ) ;
 if ( udev_dev ) {
 usbi_dbg ( "Handling hotplug event from hotplug_poll" ) ;
 udev_hotplug_event ( udev_dev ) ;
 }
 }
 while ( udev_dev ) ;
 usbi_mutex_static_unlock ( & linux_hotplug_lock ) ;
 }