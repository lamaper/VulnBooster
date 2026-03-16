void qdev_init_gpio_in ( DeviceState * dev , qemu_irq_handler handler , int n ) {
 assert ( dev -> num_gpio_in == 0 ) ;
 dev -> num_gpio_in = n ;
 dev -> gpio_in = qemu_allocate_irqs ( handler , dev , n ) ;
 }