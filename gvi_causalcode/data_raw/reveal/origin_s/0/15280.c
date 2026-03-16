qemu_irq qdev_get_gpio_in ( DeviceState * dev , int n ) {
 assert ( n >= 0 && n < dev -> num_gpio_in ) ;
 return dev -> gpio_in [ n ] ;
 }