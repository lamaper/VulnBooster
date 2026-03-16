static void vmsvga_reset ( DeviceState * dev ) {
 struct pci_vmsvga_state_s * pci = VMWARE_SVGA ( dev ) ;
 struct vmsvga_state_s * s = & pci -> chip ;
 s -> index = 0 ;
 s -> enable = 0 ;
 s -> config = 0 ;
 s -> svgaid = SVGA_ID ;
 s -> cursor . on = 0 ;
 s -> redraw_fifo_first = 0 ;
 s -> redraw_fifo_last = 0 ;
 s -> syncing = 0 ;
 vga_dirty_log_start ( & s -> vga ) ;
 }