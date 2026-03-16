static void vfio_probe_igd_bar4_quirk(VFIOPCIDevice *vdev, int nr)

{

    struct vfio_region_info *rom = NULL, *opregion = NULL,

                            *host = NULL, *lpc = NULL;

    VFIOQuirk *quirk;

    VFIOIGDQuirk *igd;

    PCIDevice *lpc_bridge;

    int i, ret, ggms_mb, gms_mb = 0, gen;

    uint64_t *bdsm_size;

    uint32_t gmch;

    uint16_t cmd_orig, cmd;

    Error *err = NULL;



     

    if (!vfio_pci_is(vdev, PCI_VENDOR_ID_INTEL, PCI_ANY_ID) ||

        !vfio_is_vga(vdev) || nr != 4) {

        return;

    }



     

    gen = igd_gen(vdev);

    if (gen != 6 && gen != 8) {

        error_report("IGD device %s is unsupported by IGD quirks, "

                     "try SandyBridge or newer", vdev->vbasedev.name);

        return;

    }



     

    gmch = vfio_pci_read_config(&vdev->pdev, IGD_GMCH, 4);

    gmch &= ~((gen < 8 ? 0x1f : 0xff) << (gen < 8 ? 3 : 8));



     

    pci_set_long(vdev->pdev.config + IGD_GMCH, gmch);

    pci_set_long(vdev->pdev.wmask + IGD_GMCH, 0);

    pci_set_long(vdev->emulated_config_bits + IGD_GMCH, ~0);



     

    if (&vdev->pdev != pci_find_device(pci_device_root_bus(&vdev->pdev),

                                       0, PCI_DEVFN(0x2, 0))) {

        return;

    }



     

    lpc_bridge = pci_find_device(pci_device_root_bus(&vdev->pdev),

                                 0, PCI_DEVFN(0x1f, 0));

    if (lpc_bridge && !object_dynamic_cast(OBJECT(lpc_bridge),

                                           "vfio-pci-igd-lpc-bridge")) {

        error_report("IGD device %s cannot support legacy mode due to existing "

                     "devices at address 1f.0", vdev->vbasedev.name);

        return;

    }



     

    ret = vfio_get_region_info(&vdev->vbasedev,

                               VFIO_PCI_ROM_REGION_INDEX, &rom);

    if ((ret || !rom->size) && !vdev->pdev.romfile) {

        error_report("IGD device %s has no ROM, legacy mode disabled",

                     vdev->vbasedev.name);

        goto out;

    }



     

    if (vdev->pdev.qdev.hotplugged) {

        error_report("IGD device %s hotplugged, ROM disabled, "

                     "legacy mode disabled", vdev->vbasedev.name);

        vdev->rom_read_failed = true;

        goto out;

    }



     

    ret = vfio_get_dev_region_info(&vdev->vbasedev,

                        VFIO_REGION_TYPE_PCI_VENDOR_TYPE | PCI_VENDOR_ID_INTEL,

                        VFIO_REGION_SUBTYPE_INTEL_IGD_OPREGION, &opregion);

    if (ret) {

        error_report("IGD device %s does not support OpRegion access,"

                     "legacy mode disabled", vdev->vbasedev.name);

        goto out;

    }



    ret = vfio_get_dev_region_info(&vdev->vbasedev,

                        VFIO_REGION_TYPE_PCI_VENDOR_TYPE | PCI_VENDOR_ID_INTEL,

                        VFIO_REGION_SUBTYPE_INTEL_IGD_HOST_CFG, &host);

    if (ret) {

        error_report("IGD device %s does not support host bridge access,"

                     "legacy mode disabled", vdev->vbasedev.name);

        goto out;

    }



    ret = vfio_get_dev_region_info(&vdev->vbasedev,

                        VFIO_REGION_TYPE_PCI_VENDOR_TYPE | PCI_VENDOR_ID_INTEL,

                        VFIO_REGION_SUBTYPE_INTEL_IGD_LPC_CFG, &lpc);

    if (ret) {

        error_report("IGD device %s does not support LPC bridge access,"

                     "legacy mode disabled", vdev->vbasedev.name);

        goto out;

    }



     

    if (!(gmch & 0x2) && !vdev->vga && vfio_populate_vga(vdev, &err)) {

        error_reportf_err(err, ERR_PREFIX, vdev->vbasedev.name);

        error_report("IGD device %s failed to enable VGA access, "

                     "legacy mode disabled", vdev->vbasedev.name);

        goto out;

    }



     

    ret = vfio_pci_igd_lpc_init(vdev, lpc);

    if (ret) {

        error_report("IGD device %s failed to create LPC bridge, "

                     "legacy mode disabled", vdev->vbasedev.name);

        goto out;

    }



     

    ret = vfio_pci_igd_host_init(vdev, host);

    if (ret) {

        error_report("IGD device %s failed to modify host bridge, "

                     "legacy mode disabled", vdev->vbasedev.name);

        goto out;

    }



     

    ret = vfio_pci_igd_opregion_init(vdev, opregion, &err);

    if (ret) {

        error_append_hint(&err, "IGD legacy mode disabled\n");

        error_reportf_err(err, ERR_PREFIX, vdev->vbasedev.name);

        goto out;

    }



     

    quirk = g_malloc0(sizeof(*quirk));

    quirk->mem = g_new0(MemoryRegion, 2);

    quirk->nr_mem = 2;

    igd = quirk->data = g_malloc0(sizeof(*igd));

    igd->vdev = vdev;

    igd->index = ~0;

    igd->bdsm = vfio_pci_read_config(&vdev->pdev, IGD_BDSM, 4);

    igd->bdsm &= ~((1 << 20) - 1);  



    memory_region_init_io(&quirk->mem[0], OBJECT(vdev), &vfio_igd_index_quirk,

                          igd, "vfio-igd-index-quirk", 4);

    memory_region_add_subregion_overlap(vdev->bars[nr].region.mem,

                                        0, &quirk->mem[0], 1);



    memory_region_init_io(&quirk->mem[1], OBJECT(vdev), &vfio_igd_data_quirk,

                          igd, "vfio-igd-data-quirk", 4);

    memory_region_add_subregion_overlap(vdev->bars[nr].region.mem,

                                        4, &quirk->mem[1], 1);



    QLIST_INSERT_HEAD(&vdev->bars[nr].quirks, quirk, next);



     

    ggms_mb = (gmch >> (gen < 8 ? 8 : 6)) & 0x3;

    if (gen > 6) {

        ggms_mb = 1 << ggms_mb;

    }



     

    if (vdev->igd_gms) {

        if (vdev->igd_gms <= 0x10) {

            gms_mb = vdev->igd_gms * 32;

            gmch |= vdev->igd_gms << (gen < 8 ? 3 : 8);

            pci_set_long(vdev->pdev.config + IGD_GMCH, gmch);

        } else {

            error_report("Unsupported IGD GMS value 0x%x", vdev->igd_gms);

            vdev->igd_gms = 0;

        }

    }



     

    bdsm_size = g_malloc(sizeof(*bdsm_size));

    *bdsm_size = cpu_to_le64((ggms_mb + gms_mb) * 1024 * 1024);

    fw_cfg_add_file(fw_cfg_find(), "etc/igd-bdsm-size",

                    bdsm_size, sizeof(*bdsm_size));



     

    pci_set_long(vdev->pdev.config + IGD_BDSM, 0);

    pci_set_long(vdev->pdev.wmask + IGD_BDSM, ~0);

    pci_set_long(vdev->emulated_config_bits + IGD_BDSM, ~0);



     

    if (pread(vdev->vbasedev.fd, &cmd_orig, sizeof(cmd_orig),

              vdev->config_offset + PCI_COMMAND) != sizeof(cmd_orig)) {

        error_report("IGD device %s - failed to read PCI command register",

                     vdev->vbasedev.name);

    }



    cmd = cmd_orig | PCI_COMMAND_IO;



    if (pwrite(vdev->vbasedev.fd, &cmd, sizeof(cmd),

               vdev->config_offset + PCI_COMMAND) != sizeof(cmd)) {

        error_report("IGD device %s - failed to write PCI command register",

                     vdev->vbasedev.name);

    }



    for (i = 1; i < vfio_igd_gtt_max(vdev); i += 4) {

        vfio_region_write(&vdev->bars[4].region, 0, i, 4);

        vfio_region_write(&vdev->bars[4].region, 4, 0, 4);

    }



    if (pwrite(vdev->vbasedev.fd, &cmd_orig, sizeof(cmd_orig),

               vdev->config_offset + PCI_COMMAND) != sizeof(cmd_orig)) {

        error_report("IGD device %s - failed to restore PCI command register",

                     vdev->vbasedev.name);

    }



    trace_vfio_pci_igd_bdsm_enabled(vdev->vbasedev.name, ggms_mb + gms_mb);



out:

    g_free(rom);

    g_free(opregion);

    g_free(host);

    g_free(lpc);

}
