void qdev_connect_gpio_out ( DeviceState * dev , int n , qemu_irq pin ) {
 assert ( n >= 0 && n < dev -> num_gpio_out ) ;
 dev -> gpio_out [ n ] = pin ;
 }