void qemu_spice_add_memslot(SimpleSpiceDisplay *ssd, QXLDevMemSlot *memslot,

                            qxl_async_io async)

{

    if (async != QXL_SYNC) {


        spice_qxl_add_memslot_async(&ssd->qxl, memslot, 0);


        abort();


    } else {

        ssd->worker->add_memslot(ssd->worker, memslot);

    }

}
