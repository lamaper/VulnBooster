static void slavio_powerdown_req ( Notifier * n , void * opaque ) {
 qemu_irq_raise ( slavio_system_powerdown ) ;
 }