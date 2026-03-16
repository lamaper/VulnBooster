void ide_dma_cancel(BMDMAState *bm)

{

    if (bm->status & BM_STATUS_DMAING) {

        bm->status &= ~BM_STATUS_DMAING;

         

        bm->unit = -1;

        bm->dma_cb = NULL;

        if (bm->aiocb) {


            printf("aio_cancel\n");


            bdrv_aio_cancel(bm->aiocb);

            bm->aiocb = NULL;

        }

    }

}
