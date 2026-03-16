struct omap_mpu_state_s *omap2420_mpu_init(MemoryRegion *sysmem,

                unsigned long sdram_size,

                const char *core)

{

    struct omap_mpu_state_s *s = g_new0(struct omap_mpu_state_s, 1);

    qemu_irq dma_irqs[4];

    DriveInfo *dinfo;

    int i;

    SysBusDevice *busdev;

    struct omap_target_agent_s *ta;



     

    s->mpu_model = omap2420;

    s->cpu = cpu_arm_init(core ?: "arm1136-r2");

    if (s->cpu == NULL) {

        fprintf(stderr, "Unable to find CPU definition\n");

        exit(1);

    }

    s->sdram_size = sdram_size;

    s->sram_size = OMAP242X_SRAM_SIZE;



    s->wakeup = qemu_allocate_irq(omap_mpu_wakeup, s, 0);



     

    omap_clk_init(s);



     

    memory_region_allocate_system_memory(&s->sdram, NULL, "omap2.dram",

                                         s->sdram_size);

    memory_region_add_subregion(sysmem, OMAP2_Q2_BASE, &s->sdram);

    memory_region_init_ram(&s->sram, NULL, "omap2.sram", s->sram_size,

                           &error_abort);

    vmstate_register_ram_global(&s->sram);

    memory_region_add_subregion(sysmem, OMAP2_SRAM_BASE, &s->sram);



    s->l4 = omap_l4_init(sysmem, OMAP2_L4_BASE, 54);



     

    s->ih[0] = qdev_create(NULL, "omap2-intc");

    qdev_prop_set_uint8(s->ih[0], "revision", 0x21);

    qdev_prop_set_ptr(s->ih[0], "fclk", omap_findclk(s, "mpu_intc_fclk"));

    qdev_prop_set_ptr(s->ih[0], "iclk", omap_findclk(s, "mpu_intc_iclk"));

    qdev_init_nofail(s->ih[0]);

    busdev = SYS_BUS_DEVICE(s->ih[0]);

    sysbus_connect_irq(busdev, 0,

                       qdev_get_gpio_in(DEVICE(s->cpu), ARM_CPU_IRQ));

    sysbus_connect_irq(busdev, 1,

                       qdev_get_gpio_in(DEVICE(s->cpu), ARM_CPU_FIQ));

    sysbus_mmio_map(busdev, 0, 0x480fe000);

    s->prcm = omap_prcm_init(omap_l4tao(s->l4, 3),

                             qdev_get_gpio_in(s->ih[0],

                                              OMAP_INT_24XX_PRCM_MPU_IRQ),

                             NULL, NULL, s);



    s->sysc = omap_sysctl_init(omap_l4tao(s->l4, 1),

                    omap_findclk(s, "omapctrl_iclk"), s);



    for (i = 0; i < 4; i++) {

        dma_irqs[i] = qdev_get_gpio_in(s->ih[omap2_dma_irq_map[i].ih],

                                       omap2_dma_irq_map[i].intr);

    }

    s->dma = omap_dma4_init(0x48056000, dma_irqs, sysmem, s, 256, 32,

                    omap_findclk(s, "sdma_iclk"),

                    omap_findclk(s, "sdma_fclk"));

    s->port->addr_valid = omap2_validate_addr;



     

    soc_dma_port_add_mem(s->dma, memory_region_get_ram_ptr(&s->sdram),

                         OMAP2_Q2_BASE, s->sdram_size);

    soc_dma_port_add_mem(s->dma, memory_region_get_ram_ptr(&s->sram),

                         OMAP2_SRAM_BASE, s->sram_size);



    s->uart[0] = omap2_uart_init(sysmem, omap_l4ta(s->l4, 19),

                                 qdev_get_gpio_in(s->ih[0],

                                                  OMAP_INT_24XX_UART1_IRQ),

                    omap_findclk(s, "uart1_fclk"),

                    omap_findclk(s, "uart1_iclk"),

                    s->drq[OMAP24XX_DMA_UART1_TX],

                    s->drq[OMAP24XX_DMA_UART1_RX],

                    "uart1",

                    serial_hds[0]);

    s->uart[1] = omap2_uart_init(sysmem, omap_l4ta(s->l4, 20),

                                 qdev_get_gpio_in(s->ih[0],

                                                  OMAP_INT_24XX_UART2_IRQ),

                    omap_findclk(s, "uart2_fclk"),

                    omap_findclk(s, "uart2_iclk"),

                    s->drq[OMAP24XX_DMA_UART2_TX],

                    s->drq[OMAP24XX_DMA_UART2_RX],

                    "uart2",

                    serial_hds[0] ? serial_hds[1] : NULL);

    s->uart[2] = omap2_uart_init(sysmem, omap_l4ta(s->l4, 21),

                                 qdev_get_gpio_in(s->ih[0],

                                                  OMAP_INT_24XX_UART3_IRQ),

                    omap_findclk(s, "uart3_fclk"),

                    omap_findclk(s, "uart3_iclk"),

                    s->drq[OMAP24XX_DMA_UART3_TX],

                    s->drq[OMAP24XX_DMA_UART3_RX],

                    "uart3",

                    serial_hds[0] && serial_hds[1] ? serial_hds[2] : NULL);



    s->gptimer[0] = omap_gp_timer_init(omap_l4ta(s->l4, 7),

                    qdev_get_gpio_in(s->ih[0], OMAP_INT_24XX_GPTIMER1),

                    omap_findclk(s, "wu_gpt1_clk"),

                    omap_findclk(s, "wu_l4_iclk"));

    s->gptimer[1] = omap_gp_timer_init(omap_l4ta(s->l4, 8),

                    qdev_get_gpio_in(s->ih[0], OMAP_INT_24XX_GPTIMER2),

                    omap_findclk(s, "core_gpt2_clk"),

                    omap_findclk(s, "core_l4_iclk"));

    s->gptimer[2] = omap_gp_timer_init(omap_l4ta(s->l4, 22),

                    qdev_get_gpio_in(s->ih[0], OMAP_INT_24XX_GPTIMER3),

                    omap_findclk(s, "core_gpt3_clk"),

                    omap_findclk(s, "core_l4_iclk"));

    s->gptimer[3] = omap_gp_timer_init(omap_l4ta(s->l4, 23),

                    qdev_get_gpio_in(s->ih[0], OMAP_INT_24XX_GPTIMER4),

                    omap_findclk(s, "core_gpt4_clk"),

                    omap_findclk(s, "core_l4_iclk"));

    s->gptimer[4] = omap_gp_timer_init(omap_l4ta(s->l4, 24),

                    qdev_get_gpio_in(s->ih[0], OMAP_INT_24XX_GPTIMER5),

                    omap_findclk(s, "core_gpt5_clk"),

                    omap_findclk(s, "core_l4_iclk"));

    s->gptimer[5] = omap_gp_timer_init(omap_l4ta(s->l4, 25),

                    qdev_get_gpio_in(s->ih[0], OMAP_INT_24XX_GPTIMER6),

                    omap_findclk(s, "core_gpt6_clk"),

                    omap_findclk(s, "core_l4_iclk"));

    s->gptimer[6] = omap_gp_timer_init(omap_l4ta(s->l4, 26),

                    qdev_get_gpio_in(s->ih[0], OMAP_INT_24XX_GPTIMER7),

                    omap_findclk(s, "core_gpt7_clk"),

                    omap_findclk(s, "core_l4_iclk"));

    s->gptimer[7] = omap_gp_timer_init(omap_l4ta(s->l4, 27),

                    qdev_get_gpio_in(s->ih[0], OMAP_INT_24XX_GPTIMER8),

                    omap_findclk(s, "core_gpt8_clk"),

                    omap_findclk(s, "core_l4_iclk"));

    s->gptimer[8] = omap_gp_timer_init(omap_l4ta(s->l4, 28),

                    qdev_get_gpio_in(s->ih[0], OMAP_INT_24XX_GPTIMER9),

                    omap_findclk(s, "core_gpt9_clk"),

                    omap_findclk(s, "core_l4_iclk"));

    s->gptimer[9] = omap_gp_timer_init(omap_l4ta(s->l4, 29),

                    qdev_get_gpio_in(s->ih[0], OMAP_INT_24XX_GPTIMER10),

                    omap_findclk(s, "core_gpt10_clk"),

                    omap_findclk(s, "core_l4_iclk"));

    s->gptimer[10] = omap_gp_timer_init(omap_l4ta(s->l4, 30),

                    qdev_get_gpio_in(s->ih[0], OMAP_INT_24XX_GPTIMER11),

                    omap_findclk(s, "core_gpt11_clk"),

                    omap_findclk(s, "core_l4_iclk"));

    s->gptimer[11] = omap_gp_timer_init(omap_l4ta(s->l4, 31),

                    qdev_get_gpio_in(s->ih[0], OMAP_INT_24XX_GPTIMER12),

                    omap_findclk(s, "core_gpt12_clk"),

                    omap_findclk(s, "core_l4_iclk"));



    omap_tap_init(omap_l4ta(s->l4, 2), s);



    s->synctimer = omap_synctimer_init(omap_l4tao(s->l4, 2), s,

                    omap_findclk(s, "clk32-kHz"),

                    omap_findclk(s, "core_l4_iclk"));



    s->i2c[0] = qdev_create(NULL, "omap_i2c");

    qdev_prop_set_uint8(s->i2c[0], "revision", 0x34);

    qdev_prop_set_ptr(s->i2c[0], "iclk", omap_findclk(s, "i2c1.iclk"));

    qdev_prop_set_ptr(s->i2c[0], "fclk", omap_findclk(s, "i2c1.fclk"));

    qdev_init_nofail(s->i2c[0]);

    busdev = SYS_BUS_DEVICE(s->i2c[0]);

    sysbus_connect_irq(busdev, 0,

                       qdev_get_gpio_in(s->ih[0], OMAP_INT_24XX_I2C1_IRQ));

    sysbus_connect_irq(busdev, 1, s->drq[OMAP24XX_DMA_I2C1_TX]);

    sysbus_connect_irq(busdev, 2, s->drq[OMAP24XX_DMA_I2C1_RX]);

    sysbus_mmio_map(busdev, 0, omap_l4_region_base(omap_l4tao(s->l4, 5), 0));



    s->i2c[1] = qdev_create(NULL, "omap_i2c");

    qdev_prop_set_uint8(s->i2c[1], "revision", 0x34);

    qdev_prop_set_ptr(s->i2c[1], "iclk", omap_findclk(s, "i2c2.iclk"));

    qdev_prop_set_ptr(s->i2c[1], "fclk", omap_findclk(s, "i2c2.fclk"));

    qdev_init_nofail(s->i2c[1]);

    busdev = SYS_BUS_DEVICE(s->i2c[1]);

    sysbus_connect_irq(busdev, 0,

                       qdev_get_gpio_in(s->ih[0], OMAP_INT_24XX_I2C2_IRQ));

    sysbus_connect_irq(busdev, 1, s->drq[OMAP24XX_DMA_I2C2_TX]);

    sysbus_connect_irq(busdev, 2, s->drq[OMAP24XX_DMA_I2C2_RX]);

    sysbus_mmio_map(busdev, 0, omap_l4_region_base(omap_l4tao(s->l4, 6), 0));



    s->gpio = qdev_create(NULL, "omap2-gpio");

    qdev_prop_set_int32(s->gpio, "mpu_model", s->mpu_model);

    qdev_prop_set_ptr(s->gpio, "iclk", omap_findclk(s, "gpio_iclk"));

    qdev_prop_set_ptr(s->gpio, "fclk0", omap_findclk(s, "gpio1_dbclk"));

    qdev_prop_set_ptr(s->gpio, "fclk1", omap_findclk(s, "gpio2_dbclk"));

    qdev_prop_set_ptr(s->gpio, "fclk2", omap_findclk(s, "gpio3_dbclk"));

    qdev_prop_set_ptr(s->gpio, "fclk3", omap_findclk(s, "gpio4_dbclk"));

    if (s->mpu_model == omap2430) {

        qdev_prop_set_ptr(s->gpio, "fclk4", omap_findclk(s, "gpio5_dbclk"));

    }

    qdev_init_nofail(s->gpio);

    busdev = SYS_BUS_DEVICE(s->gpio);

    sysbus_connect_irq(busdev, 0,

                       qdev_get_gpio_in(s->ih[0], OMAP_INT_24XX_GPIO_BANK1));

    sysbus_connect_irq(busdev, 3,

                       qdev_get_gpio_in(s->ih[0], OMAP_INT_24XX_GPIO_BANK2));

    sysbus_connect_irq(busdev, 6,

                       qdev_get_gpio_in(s->ih[0], OMAP_INT_24XX_GPIO_BANK3));

    sysbus_connect_irq(busdev, 9,

                       qdev_get_gpio_in(s->ih[0], OMAP_INT_24XX_GPIO_BANK4));

    if (s->mpu_model == omap2430) {

        sysbus_connect_irq(busdev, 12,

                           qdev_get_gpio_in(s->ih[0],

                                            OMAP_INT_243X_GPIO_BANK5));

    }

    ta = omap_l4ta(s->l4, 3);

    sysbus_mmio_map(busdev, 0, omap_l4_region_base(ta, 1));

    sysbus_mmio_map(busdev, 1, omap_l4_region_base(ta, 0));

    sysbus_mmio_map(busdev, 2, omap_l4_region_base(ta, 2));

    sysbus_mmio_map(busdev, 3, omap_l4_region_base(ta, 4));

    sysbus_mmio_map(busdev, 4, omap_l4_region_base(ta, 5));



    s->sdrc = omap_sdrc_init(sysmem, 0x68009000);

    s->gpmc = omap_gpmc_init(s, 0x6800a000,

                             qdev_get_gpio_in(s->ih[0], OMAP_INT_24XX_GPMC_IRQ),

                             s->drq[OMAP24XX_DMA_GPMC]);



    dinfo = drive_get(IF_SD, 0, 0);

    if (!dinfo) {

        fprintf(stderr, "qemu: missing SecureDigital device\n");

        exit(1);

    }

    s->mmc = omap2_mmc_init(omap_l4tao(s->l4, 9),

                    blk_by_legacy_dinfo(dinfo),

                    qdev_get_gpio_in(s->ih[0], OMAP_INT_24XX_MMC_IRQ),

                    &s->drq[OMAP24XX_DMA_MMC1_TX],

                    omap_findclk(s, "mmc_fclk"), omap_findclk(s, "mmc_iclk"));



    s->mcspi[0] = omap_mcspi_init(omap_l4ta(s->l4, 35), 4,

                    qdev_get_gpio_in(s->ih[0], OMAP_INT_24XX_MCSPI1_IRQ),

                    &s->drq[OMAP24XX_DMA_SPI1_TX0],

                    omap_findclk(s, "spi1_fclk"),

                    omap_findclk(s, "spi1_iclk"));

    s->mcspi[1] = omap_mcspi_init(omap_l4ta(s->l4, 36), 2,

                    qdev_get_gpio_in(s->ih[0], OMAP_INT_24XX_MCSPI2_IRQ),

                    &s->drq[OMAP24XX_DMA_SPI2_TX0],

                    omap_findclk(s, "spi2_fclk"),

                    omap_findclk(s, "spi2_iclk"));



    s->dss = omap_dss_init(omap_l4ta(s->l4, 10), sysmem, 0x68000800,

                     

                    qdev_get_gpio_in(s->ih[0], OMAP_INT_24XX_DSS_IRQ),

                           s->drq[OMAP24XX_DMA_DSS],

                    omap_findclk(s, "dss_clk1"), omap_findclk(s, "dss_clk2"),

                    omap_findclk(s, "dss_54m_clk"),

                    omap_findclk(s, "dss_l3_iclk"),

                    omap_findclk(s, "dss_l4_iclk"));



    omap_sti_init(omap_l4ta(s->l4, 18), sysmem, 0x54000000,

                  qdev_get_gpio_in(s->ih[0], OMAP_INT_24XX_STI),

                  omap_findclk(s, "emul_ck"),

                    serial_hds[0] && serial_hds[1] && serial_hds[2] ?

                    serial_hds[3] : NULL);



    s->eac = omap_eac_init(omap_l4ta(s->l4, 32),

                           qdev_get_gpio_in(s->ih[0], OMAP_INT_24XX_EAC_IRQ),

                     

                    &s->drq[OMAP24XX_DMA_EAC_AC_RD],

                    omap_findclk(s, "func_96m_clk"),

                    omap_findclk(s, "core_l4_iclk"));



     



    qemu_register_reset(omap2_mpu_reset, s);



    return s;

}
