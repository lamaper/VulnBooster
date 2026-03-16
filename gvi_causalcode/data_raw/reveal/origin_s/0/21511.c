void macio_ide_register_dma ( MACIOIDEState * s , void * dbdma , int channel ) {
 s -> dbdma = dbdma ;
 DBDMA_register_channel ( dbdma , channel , s -> dma_irq , pmac_ide_transfer , pmac_ide_flush , s ) ;
 }