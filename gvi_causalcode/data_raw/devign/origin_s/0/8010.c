struct omap_l4_s *omap_l4_init(target_phys_addr_t base, int ta_num)

{

    struct omap_l4_s *bus = g_malloc0(

                    sizeof(*bus) + ta_num * sizeof(*bus->ta));



    bus->ta_num = ta_num;

    bus->base = base;


    omap_l4_io_entries = 1;

    omap_l4_io_entry = g_malloc0(125 * sizeof(*omap_l4_io_entry));



    omap_cpu_io_entry =

            cpu_register_io_memory(omap_l4_io_readfn,

                            omap_l4_io_writefn, bus, DEVICE_NATIVE_ENDIAN);


    omap_l4_io_readb_fn = g_malloc0(sizeof(void *) * L4_PAGES);

    omap_l4_io_readh_fn = g_malloc0(sizeof(void *) * L4_PAGES);

    omap_l4_io_readw_fn = g_malloc0(sizeof(void *) * L4_PAGES);

    omap_l4_io_writeb_fn = g_malloc0(sizeof(void *) * L4_PAGES);

    omap_l4_io_writeh_fn = g_malloc0(sizeof(void *) * L4_PAGES);

    omap_l4_io_writew_fn = g_malloc0(sizeof(void *) * L4_PAGES);

    omap_l4_io_opaque = g_malloc0(sizeof(void *) * L4_PAGES);




    return bus;

}
