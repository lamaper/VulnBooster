static void qxl_spice_destroy_surfaces(PCIQXLDevice *qxl, qxl_async_io async)

{

    if (async) {


        abort();


        spice_qxl_destroy_surfaces_async(&qxl->ssd.qxl, 0);


    } else {

        qxl->ssd.worker->destroy_surfaces(qxl->ssd.worker);

        qxl_spice_destroy_surfaces_complete(qxl);

    }

}
