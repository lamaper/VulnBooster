static void ppc_core99_init (int ram_size, int vga_ram_size,

                             const char *boot_device, DisplayState *ds,

                             const char **fd_filename, int snapshot,

                             const char *kernel_filename,

                             const char *kernel_cmdline,

                             const char *initrd_filename,

                             const char *cpu_model)

{

    CPUState *env = NULL, *envs[MAX_CPUS];

    char buf[1024];

    qemu_irq *pic, **openpic_irqs;

    int unin_memory;

    int linux_boot, i;

    unsigned long bios_offset, vga_bios_offset;

    uint32_t kernel_base, kernel_size, initrd_base, initrd_size;

    PCIBus *pci_bus;

    nvram_t nvram;


    MacIONVRAMState *nvr;

    int nvram_mem_index;


    m48t59_t *m48t59;

    int vga_bios_size, bios_size;

    qemu_irq *dummy_irq;

    int pic_mem_index, dbdma_mem_index, cuda_mem_index;

    int ide_mem_index[2];

    int ppc_boot_device = boot_device[0];



    linux_boot = (kernel_filename != NULL);



     

    if (cpu_model == NULL)

        cpu_model = "default";

    for (i = 0; i < smp_cpus; i++) {

        env = cpu_init(cpu_model);

        if (!env) {

            fprintf(stderr, "Unable to find PowerPC CPU definition\n");

            exit(1);

        }

         

        cpu_ppc_tb_init(env, 100UL * 1000UL * 1000UL);


        env->osi_call = vga_osi_call;


        qemu_register_reset(&cpu_ppc_reset, env);

        register_savevm("cpu", 0, 3, cpu_save, cpu_load, env);

        envs[i] = env;

    }

    if (env->nip < 0xFFF80000) {

         

        cpu_abort(env, "Mac99 hardware can not handle 1 MB BIOS\n");

    }



     

    cpu_register_physical_memory(0, ram_size, IO_MEM_RAM);



     

    bios_offset = ram_size + vga_ram_size;

    if (bios_name == NULL)

        bios_name = BIOS_FILENAME;

    snprintf(buf, sizeof(buf), "%s/%s", bios_dir, bios_name);

    bios_size = load_image(buf, phys_ram_base + bios_offset);

    if (bios_size < 0 || bios_size > BIOS_SIZE) {

        cpu_abort(env, "qemu: could not load PowerPC bios '%s'\n", buf);

        exit(1);

    }

    bios_size = (bios_size + 0xfff) & ~0xfff;

    if (bios_size > 0x00080000) {

         

        cpu_abort(env, "Mac99 hardware can not handle 1 MB BIOS\n");

    }

    cpu_register_physical_memory((uint32_t)(-bios_size),

                                 bios_size, bios_offset | IO_MEM_ROM);



     

    vga_bios_offset = bios_offset + bios_size;

    snprintf(buf, sizeof(buf), "%s/%s", bios_dir, VGABIOS_FILENAME);

    vga_bios_size = load_image(buf, phys_ram_base + vga_bios_offset + 8);

    if (vga_bios_size < 0) {

         

        fprintf(stderr, "qemu: warning: could not load VGA bios '%s'\n", buf);

        vga_bios_size = 0;

    } else {

         

        phys_ram_base[vga_bios_offset] = 'N';

        phys_ram_base[vga_bios_offset + 1] = 'D';

        phys_ram_base[vga_bios_offset + 2] = 'R';

        phys_ram_base[vga_bios_offset + 3] = 'V';

        cpu_to_be32w((uint32_t *)(phys_ram_base + vga_bios_offset + 4),

                     vga_bios_size);

        vga_bios_size += 8;

    }

    vga_bios_size = (vga_bios_size + 0xfff) & ~0xfff;



    if (linux_boot) {

        kernel_base = KERNEL_LOAD_ADDR;

         

        kernel_size = load_image(kernel_filename, phys_ram_base + kernel_base);

        if (kernel_size < 0) {

            cpu_abort(env, "qemu: could not load kernel '%s'\n",

                      kernel_filename);

            exit(1);

        }

         

        if (initrd_filename) {

            initrd_base = INITRD_LOAD_ADDR;

            initrd_size = load_image(initrd_filename,

                                     phys_ram_base + initrd_base);

            if (initrd_size < 0) {

                cpu_abort(env, "qemu: could not load initial ram disk '%s'\n",

                          initrd_filename);

                exit(1);

            }

        } else {

            initrd_base = 0;

            initrd_size = 0;

        }

        ppc_boot_device = 'm';

    } else {

        kernel_base = 0;

        kernel_size = 0;

        initrd_base = 0;

        initrd_size = 0;

    }



    isa_mem_base = 0x80000000;



     

    isa_mmio_init(0xf2000000, 0x00800000);



     

    unin_memory = cpu_register_io_memory(0, unin_read, unin_write, NULL);

    cpu_register_physical_memory(0xf8000000, 0x00001000, unin_memory);



    openpic_irqs = qemu_mallocz(smp_cpus * sizeof(qemu_irq *));

    openpic_irqs[0] =

        qemu_mallocz(smp_cpus * sizeof(qemu_irq) * OPENPIC_OUTPUT_NB);

    for (i = 0; i < smp_cpus; i++) {

         

        switch (PPC_INPUT(env)) {

        case PPC_FLAGS_INPUT_6xx:

            openpic_irqs[i] = openpic_irqs[0] + (i * OPENPIC_OUTPUT_NB);

            openpic_irqs[i][OPENPIC_OUTPUT_INT] =

                ((qemu_irq *)env->irq_inputs)[PPC6xx_INPUT_INT];

            openpic_irqs[i][OPENPIC_OUTPUT_CINT] =

                ((qemu_irq *)env->irq_inputs)[PPC6xx_INPUT_INT];

            openpic_irqs[i][OPENPIC_OUTPUT_MCK] =

                ((qemu_irq *)env->irq_inputs)[PPC6xx_INPUT_MCP];

             

            openpic_irqs[i][OPENPIC_OUTPUT_DEBUG] = NULL;

             

            openpic_irqs[i][OPENPIC_OUTPUT_RESET] =

                ((qemu_irq *)env->irq_inputs)[PPC6xx_INPUT_HRESET];

            break;


        case PPC_FLAGS_INPUT_970:

            openpic_irqs[i] = openpic_irqs[0] + (i * OPENPIC_OUTPUT_NB);

            openpic_irqs[i][OPENPIC_OUTPUT_INT] =

                ((qemu_irq *)env->irq_inputs)[PPC970_INPUT_INT];

            openpic_irqs[i][OPENPIC_OUTPUT_CINT] =

                ((qemu_irq *)env->irq_inputs)[PPC970_INPUT_INT];

            openpic_irqs[i][OPENPIC_OUTPUT_MCK] =

                ((qemu_irq *)env->irq_inputs)[PPC970_INPUT_MCP];

             

            openpic_irqs[i][OPENPIC_OUTPUT_DEBUG] = NULL;

             

            openpic_irqs[i][OPENPIC_OUTPUT_RESET] =

                ((qemu_irq *)env->irq_inputs)[PPC970_INPUT_HRESET];

            break;


        default:

            cpu_abort(env, "Bus model not supported on mac99 machine\n");

            exit(1);

        }

    }

    pic = openpic_init(NULL, &pic_mem_index, smp_cpus, openpic_irqs, NULL);

    pci_bus = pci_pmac_init(pic);

     

    pci_vga_init(pci_bus, ds, phys_ram_base + ram_size,

                 ram_size, vga_ram_size,

                 vga_bios_offset, vga_bios_size);

    

     

    dummy_irq = i8259_init(NULL);



     

    serial_init(0x3f8, dummy_irq[4], serial_hds[0]);

    for(i = 0; i < nb_nics; i++) {

        if (!nd_table[i].model)

            nd_table[i].model = "ne2k_pci";

        pci_nic_init(pci_bus, &nd_table[i], -1);

    }


    ide_mem_index[0] = pmac_ide_init(&bs_table[0], pic[0x13]);

    ide_mem_index[1] = pmac_ide_init(&bs_table[2], pic[0x14]);


    pci_cmd646_ide_init(pci_bus, &bs_table[0], 0);


     

    cuda_init(&cuda_mem_index, pic[0x19]);

    

    adb_kbd_init(&adb_bus);

    adb_mouse_init(&adb_bus);



    dbdma_init(&dbdma_mem_index);



    macio_init(pci_bus, 0x0022, 0, pic_mem_index, dbdma_mem_index,

               cuda_mem_index, NULL, 2, ide_mem_index);



    if (usb_enabled) {

        usb_ohci_init_pci(pci_bus, 3, -1);

    }



    if (graphic_depth != 15 && graphic_depth != 32 && graphic_depth != 8)

        graphic_depth = 15;


     

    nvr = macio_nvram_init(&nvram_mem_index, 0x2000);

    pmac_format_nvram_partition(nvr, 0x2000);

    macio_nvram_map(nvr, 0xFFF04000);

    nvram.opaque = nvr;

    nvram.read_fn = &macio_nvram_read;

    nvram.write_fn = &macio_nvram_write;


    m48t59 = m48t59_init(dummy_irq[8], 0xFFF04000, 0x0074, NVRAM_SIZE, 59);

    nvram.opaque = m48t59;

    nvram.read_fn = &m48t59_read;

    nvram.write_fn = &m48t59_write;


    PPC_NVRAM_set_params(&nvram, NVRAM_SIZE, "MAC99", ram_size,

                         ppc_boot_device, kernel_base, kernel_size,

                         kernel_cmdline,

                         initrd_base, initrd_size,

                          

                         0,

                         graphic_width, graphic_height, graphic_depth);

     



     

    register_ioport_write(0x0F00, 4, 1, &PPC_debug_write, NULL);

 }
