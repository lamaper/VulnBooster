static void network_init ( PCIBus * pci_bus ) {
 int i ;
 for ( i = 0 ;
 i < nb_nics ;
 i ++ ) {
 NICInfo * nd = & nd_table [ i ] ;
 const char * default_devaddr = NULL ;
 if ( i == 0 && ( ! nd -> model || strcmp ( nd -> model , "rtl8139" ) == 0 ) ) {
 default_devaddr = "07" ;
 }
 pci_nic_init_nofail ( nd , pci_bus , "rtl8139" , default_devaddr ) ;
 }
 }