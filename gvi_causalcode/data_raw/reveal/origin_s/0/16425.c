static void ide_dbdma_start ( IDEDMA * dma , IDEState * s , BlockCompletionFunc * cb ) {
 MACIOIDEState * m = container_of ( dma , MACIOIDEState , dma ) ;
 MACIO_DPRINTF ( "\n" ) ;
 m -> dma_active = true ;
 DBDMA_kick ( m -> dbdma ) ;
 }