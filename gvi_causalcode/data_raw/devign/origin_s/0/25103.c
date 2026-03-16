static void ppc_spapr_init(MachineState *machine)

{

    sPAPRMachineState *spapr = SPAPR_MACHINE(machine);

    sPAPRMachineClass *smc = SPAPR_MACHINE_GET_CLASS(machine);

    const char *kernel_filename = machine->kernel_filename;

    const char *kernel_cmdline = machine->kernel_cmdline;

    const char *initrd_filename = machine->initrd_filename;

    PowerPCCPU *cpu;

    PCIHostState *phb;

    int i;

    MemoryRegion *sysmem = get_system_memory();

    MemoryRegion *ram = g_new(MemoryRegion, 1);

    MemoryRegion *rma_region;

    void *rma = NULL;

    hwaddr rma_alloc_size;

    hwaddr node0_size = spapr_node0_size();

    uint32_t initrd_base = 0;

    long kernel_size = 0, initrd_size = 0;

    long load_limit, fw_size;

    bool kernel_le = false;

    char *filename;



    msi_supported = true;



    QLIST_INIT(&spapr->phbs);



    cpu_ppc_hypercall = emulate_spapr_hypercall;



     

    rma_alloc_size = kvmppc_alloc_rma(&rma);



    if (rma_alloc_size == -1) {

        error_report("Unable to create RMA");

        exit(1);

    }



    if (rma_alloc_size && (rma_alloc_size < node0_size)) {

        spapr->rma_size = rma_alloc_size;

    } else {

        spapr->rma_size = node0_size;



         

        if (kvm_enabled()) {

            spapr->vrma_adjust = 1;

            spapr->rma_size = MIN(spapr->rma_size, 0x10000000);

        }

    }



    if (spapr->rma_size > node0_size) {

        error_report("Numa node 0 has to span the RMA (%#08"HWADDR_PRIx")",

                     spapr->rma_size);

        exit(1);

    }



     

    load_limit = MIN(spapr->rma_size, RTAS_MAX_ADDR) - FW_OVERHEAD;



     

    spapr->htab_shift = 18;  

    while (spapr->htab_shift <= 46) {

        if ((1ULL << (spapr->htab_shift + 7)) >= machine->maxram_size) {

            break;

        }

        spapr->htab_shift++;

    }

    spapr_alloc_htab(spapr);



     

    spapr->icp = xics_system_init(machine,

                                  DIV_ROUND_UP(max_cpus * kvmppc_smt_threads(),

                                               smp_threads),

                                  XICS_IRQS, &error_fatal);



    if (smc->dr_lmb_enabled) {

        spapr_validate_node_memory(machine, &error_fatal);

    }



     

    if (machine->cpu_model == NULL) {

        machine->cpu_model = kvm_enabled() ? "host" : "POWER7";

    }

    for (i = 0; i < smp_cpus; i++) {

        cpu = cpu_ppc_init(machine->cpu_model);

        if (cpu == NULL) {

            error_report("Unable to find PowerPC CPU definition");

            exit(1);

        }

        spapr_cpu_init(spapr, cpu, &error_fatal);

    }



    if (kvm_enabled()) {

         

        kvmppc_enable_logical_ci_hcalls();

        kvmppc_enable_set_mode_hcall();

    }



     

    memory_region_allocate_system_memory(ram, NULL, "ppc_spapr.ram",

                                         machine->ram_size);

    memory_region_add_subregion(sysmem, 0, ram);



    if (rma_alloc_size && rma) {

        rma_region = g_new(MemoryRegion, 1);

        memory_region_init_ram_ptr(rma_region, NULL, "ppc_spapr.rma",

                                   rma_alloc_size, rma);

        vmstate_register_ram_global(rma_region);

        memory_region_add_subregion(sysmem, 0, rma_region);

    }



     

    if (machine->ram_size < machine->maxram_size) {

        ram_addr_t hotplug_mem_size = machine->maxram_size - machine->ram_size;



        if (machine->ram_slots > SPAPR_MAX_RAM_SLOTS) {

            error_report("Specified number of memory slots %"

                         PRIu64" exceeds max supported %d",

                         machine->ram_slots, SPAPR_MAX_RAM_SLOTS);

            exit(1);

        }



        spapr->hotplug_memory.base = ROUND_UP(machine->ram_size,

                                              SPAPR_HOTPLUG_MEM_ALIGN);

        memory_region_init(&spapr->hotplug_memory.mr, OBJECT(spapr),

                           "hotplug-memory", hotplug_mem_size);

        memory_region_add_subregion(sysmem, spapr->hotplug_memory.base,

                                    &spapr->hotplug_memory.mr);

    }



    if (smc->dr_lmb_enabled) {

        spapr_create_lmb_dr_connectors(spapr);

    }



    filename = qemu_find_file(QEMU_FILE_TYPE_BIOS, "spapr-rtas.bin");

    if (!filename) {

        error_report("Could not find LPAR rtas '%s'", "spapr-rtas.bin");

        exit(1);

    }

    spapr->rtas_size = get_image_size(filename);

    spapr->rtas_blob = g_malloc(spapr->rtas_size);

    if (load_image_size(filename, spapr->rtas_blob, spapr->rtas_size) < 0) {

        error_report("Could not load LPAR rtas '%s'", filename);

        exit(1);

    }

    if (spapr->rtas_size > RTAS_MAX_SIZE) {

        error_report("RTAS too big ! 0x%zx bytes (max is 0x%x)",

                     (size_t)spapr->rtas_size, RTAS_MAX_SIZE);

        exit(1);

    }

    g_free(filename);



     

    spapr_events_init(spapr);



     

    spapr_rtc_create(spapr);



     

    spapr->vio_bus = spapr_vio_bus_init();



    for (i = 0; i < MAX_SERIAL_PORTS; i++) {

        if (serial_hds[i]) {

            spapr_vty_create(spapr->vio_bus, serial_hds[i]);

        }

    }



     

    spapr_create_nvram(spapr);



     

    spapr_pci_rtas_init();



    phb = spapr_create_phb(spapr, 0);



    for (i = 0; i < nb_nics; i++) {

        NICInfo *nd = &nd_table[i];



        if (!nd->model) {

            nd->model = g_strdup("ibmveth");

        }



        if (strcmp(nd->model, "ibmveth") == 0) {

            spapr_vlan_create(spapr->vio_bus, nd);

        } else {

            pci_nic_init_nofail(&nd_table[i], phb->bus, nd->model, NULL);

        }

    }



    for (i = 0; i <= drive_get_max_bus(IF_SCSI); i++) {

        spapr_vscsi_create(spapr->vio_bus);

    }



     

    if (spapr_vga_init(phb->bus, &error_fatal)) {

        spapr->has_graphics = true;

        machine->usb |= defaults_enabled() && !machine->usb_disabled;

    }



    if (machine->usb) {

        if (smc->use_ohci_by_default) {

            pci_create_simple(phb->bus, -1, "pci-ohci");

        } else {

            pci_create_simple(phb->bus, -1, "nec-usb-xhci");

        }



        if (spapr->has_graphics) {

            USBBus *usb_bus = usb_bus_find(-1);



            usb_create_simple(usb_bus, "usb-kbd");

            usb_create_simple(usb_bus, "usb-mouse");

        }

    }



    if (spapr->rma_size < (MIN_RMA_SLOF << 20)) {

        error_report(

            "pSeries SLOF firmware requires >= %ldM guest RMA (Real Mode Area memory)",

            MIN_RMA_SLOF);

        exit(1);

    }



    if (kernel_filename) {

        uint64_t lowaddr = 0;



        kernel_size = load_elf(kernel_filename, translate_kernel_address, NULL,

                               NULL, &lowaddr, NULL, 1, PPC_ELF_MACHINE, 0);

        if (kernel_size == ELF_LOAD_WRONG_ENDIAN) {

            kernel_size = load_elf(kernel_filename,

                                   translate_kernel_address, NULL,

                                   NULL, &lowaddr, NULL, 0, PPC_ELF_MACHINE, 0);

            kernel_le = kernel_size > 0;

        }

        if (kernel_size < 0) {

            error_report("error loading %s: %s",

                         kernel_filename, load_elf_strerror(kernel_size));

            exit(1);

        }



         

        if (initrd_filename) {

             

            initrd_base = (KERNEL_LOAD_ADDR + kernel_size + 0x1ffff) & ~0xffff;

            initrd_size = load_image_targphys(initrd_filename, initrd_base,

                                              load_limit - initrd_base);

            if (initrd_size < 0) {

                error_report("could not load initial ram disk '%s'",

                             initrd_filename);

                exit(1);

            }

        } else {

            initrd_base = 0;

            initrd_size = 0;

        }

    }



    if (bios_name == NULL) {

        bios_name = FW_FILE_NAME;

    }

    filename = qemu_find_file(QEMU_FILE_TYPE_BIOS, bios_name);

    if (!filename) {

        error_report("Could not find LPAR firmware '%s'", bios_name);

        exit(1);

    }

    fw_size = load_image_targphys(filename, 0, FW_MAX_SIZE);

    if (fw_size <= 0) {

        error_report("Could not load LPAR firmware '%s'", filename);

        exit(1);

    }

    g_free(filename);



     

    vmstate_register(NULL, 0, &vmstate_spapr, spapr);

    register_savevm_live(NULL, "spapr/htab", -1, 1,

                         &savevm_htab_handlers, spapr);



     

    spapr->fdt_skel = spapr_create_fdt_skel(initrd_base, initrd_size,

                                            kernel_size, kernel_le,

                                            kernel_cmdline,

                                            spapr->check_exception_irq);

    assert(spapr->fdt_skel != NULL);



     

    QTAILQ_INIT(&spapr->ccs_list);

    qemu_register_reset(spapr_ccs_reset_hook, spapr);



    qemu_register_boot_set(spapr_boot_set, spapr);

}
