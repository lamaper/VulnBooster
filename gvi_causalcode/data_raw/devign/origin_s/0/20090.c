static void ppc_prep_init (int ram_size, int vga_ram_size,

                           const char *boot_device, DisplayState *ds,

                           const char *kernel_filename,

                           const char *kernel_cmdline,

                           const char *initrd_filename,

                           const char *cpu_model)

{

    CPUState *env = NULL, *envs[MAX_CPUS];

    char buf[1024];

    nvram_t nvram;

    m48t59_t *m48t59;

    int PPC_io_memory;

    int linux_boot, i, nb_nics1, bios_size;

    unsigned long bios_offset;

    uint32_t kernel_base, kernel_size, initrd_base, initrd_size;

    PCIBus *pci_bus;

    qemu_irq *i8259;

    int ppc_boot_device;



    sysctrl = qemu_mallocz(sizeof(sysctrl_t));

    if (sysctrl == NULL)

        return;



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

        qemu_register_reset(&cpu_ppc_reset, env);

        register_savevm("cpu", 0, 3, cpu_save, cpu_load, env);

        envs[i] = env;

    }



     

    cpu_register_physical_memory(0, ram_size, IO_MEM_RAM);



     

    bios_offset = ram_size + vga_ram_size;

    if (bios_name == NULL)

        bios_name = BIOS_FILENAME;

    snprintf(buf, sizeof(buf), "%s/%s", bios_dir, bios_name);

    bios_size = load_image(buf, phys_ram_base + bios_offset);

    if (bios_size < 0 || bios_size > BIOS_SIZE) {

        cpu_abort(env, "qemu: could not load PPC PREP bios '%s'\n", buf);

        exit(1);

    }

    if (env->nip < 0xFFF80000 && bios_size < 0x00100000) {

        cpu_abort(env, "PowerPC 601 / 620 / 970 need a 1MB BIOS\n");

    }

    bios_size = (bios_size + 0xfff) & ~0xfff;

    cpu_register_physical_memory((uint32_t)(-bios_size),

                                 bios_size, bios_offset | IO_MEM_ROM);



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

        ppc_boot_device = '\0';

         

        for (i = 0; boot_device[i] != '\0'; i++) {

            if (boot_device[i] >= 'a' && boot_device[i] <= 'f') {

                ppc_boot_device = boot_device[i];

                break;

            }

        }

        if (ppc_boot_device == '\0') {

            fprintf(stderr, "No valid boot device for Mac99 machine\n");

            exit(1);

        }

    }



    isa_mem_base = 0xc0000000;

    if (PPC_INPUT(env) != PPC_FLAGS_INPUT_6xx) {

        cpu_abort(env, "Only 6xx bus is supported on PREP machine\n");

        exit(1);

    }

    i8259 = i8259_init(first_cpu->irq_inputs[PPC6xx_INPUT_INT]);

    pci_bus = pci_prep_init(i8259);

     

     

    PPC_io_memory = cpu_register_io_memory(0, PPC_prep_io_read,

                                           PPC_prep_io_write, sysctrl);

    cpu_register_physical_memory(0x80000000, 0x00800000, PPC_io_memory);



     

    pci_vga_init(pci_bus, ds, phys_ram_base + ram_size, ram_size,

                 vga_ram_size, 0, 0);

     

     

    rtc_init(0x70, i8259[8]);



    serial_init(0x3f8, i8259[4], serial_hds[0]);

    nb_nics1 = nb_nics;

    if (nb_nics1 > NE2000_NB_MAX)

        nb_nics1 = NE2000_NB_MAX;

    for(i = 0; i < nb_nics1; i++) {

        if (nd_table[i].model == NULL

            || strcmp(nd_table[i].model, "ne2k_isa") == 0) {

            isa_ne2000_init(ne2000_io[i], i8259[ne2000_irq[i]], &nd_table[i]);

        } else {

            pci_nic_init(pci_bus, &nd_table[i], -1);

        }

    }



    for(i = 0; i < 2; i++) {

        isa_ide_init(ide_iobase[i], ide_iobase2[i], i8259[ide_irq[i]],

                     bs_table[2 * i], bs_table[2 * i + 1]);

    }

    i8042_init(i8259[1], i8259[12], 0x60);

    DMA_init(1);

     

     



    fdctrl_init(i8259[6], 2, 0, 0x3f0, fd_table);



     

    register_ioport_read(0x61, 1, 1, speaker_ioport_read, NULL);

    register_ioport_write(0x61, 1, 1, speaker_ioport_write, NULL);

     

    sysctrl->reset_irq = first_cpu->irq_inputs[PPC6xx_INPUT_HRESET];

    register_ioport_read(0x398, 2, 1, &PREP_io_read, sysctrl);

    register_ioport_write(0x398, 2, 1, &PREP_io_write, sysctrl);

     

    register_ioport_read(0x0092, 0x01, 1, &PREP_io_800_readb, sysctrl);

    register_ioport_write(0x0092, 0x01, 1, &PREP_io_800_writeb, sysctrl);

    register_ioport_read(0x0800, 0x52, 1, &PREP_io_800_readb, sysctrl);

    register_ioport_write(0x0800, 0x52, 1, &PREP_io_800_writeb, sysctrl);

     

    PPC_io_memory = cpu_register_io_memory(0, PPC_intack_read,

                                           PPC_intack_write, NULL);

    cpu_register_physical_memory(0xBFFFFFF0, 0x4, PPC_io_memory);


    PPC_io_memory = cpu_register_io_memory(0, PPC_XCSR_read, PPC_XCSR_write,

                                           NULL);

    cpu_register_physical_memory(0xFEFF0000, 0x1000, PPC_io_memory);




    if (usb_enabled) {

        usb_ohci_init_pci(pci_bus, 3, -1);

    }



    m48t59 = m48t59_init(i8259[8], 0, 0x0074, NVRAM_SIZE, 59);

    if (m48t59 == NULL)

        return;

    sysctrl->nvram = m48t59;



     

    nvram.opaque = m48t59;

    nvram.read_fn = &m48t59_read;

    nvram.write_fn = &m48t59_write;

    PPC_NVRAM_set_params(&nvram, NVRAM_SIZE, "PREP", ram_size, ppc_boot_device,

                         kernel_base, kernel_size,

                         kernel_cmdline,

                         initrd_base, initrd_size,

                          

                         0,

                         graphic_width, graphic_height, graphic_depth);



     

    register_ioport_write(0x0F00, 4, 1, &PPC_debug_write, NULL);

}
