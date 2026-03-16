static uint32_t e1000e_mac_ims_read ( E1000ECore * core , int index ) {
 trace_e1000e_irq_read_ims ( core -> mac [ IMS ] ) ;
 return core -> mac [ IMS ] ;
 }