static void macio_ide_realizefn ( DeviceState * dev , Error * * errp ) {
 MACIOIDEState * s = MACIO_IDE ( dev ) ;
 ide_init2 ( & s -> bus , s -> irq ) ;
 s -> dma . ops = & dbdma_ops ;
 s -> bus . dma = & s -> dma ;
 }