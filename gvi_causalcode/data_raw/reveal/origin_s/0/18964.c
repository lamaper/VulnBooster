void qdev_init_gpio_out ( DeviceState * dev , qemu_irq * pins , int n ) {
 assert ( dev -> num_gpio_out == 0 ) ;
 dev -> num_gpio_out = n ;
 dev -> gpio_out = pins ;
 }