target_phys_addr_t omap_l4_attach(struct omap_target_agent_s *ta, int region,

                int iotype)

{

    target_phys_addr_t base;

    ssize_t size;


    int i;




    if (region < 0 || region >= ta->regions) {

        fprintf(stderr, "%s: bad io region (%i)\n", __FUNCTION__, region);

        exit(-1);

    }



    base = ta->bus->base + ta->start[region].offset;

    size = ta->start[region].size;

    if (iotype) {


        cpu_register_physical_memory(base, size, iotype);


        cpu_register_physical_memory(base, size, omap_cpu_io_entry);

        i = (base - ta->bus->base) / TARGET_PAGE_SIZE;

        for (; size > 0; size -= TARGET_PAGE_SIZE, i ++) {

            omap_l4_io_readb_fn[i] = omap_l4_io_entry[iotype].mem_read[0];

            omap_l4_io_readh_fn[i] = omap_l4_io_entry[iotype].mem_read[1];

            omap_l4_io_readw_fn[i] = omap_l4_io_entry[iotype].mem_read[2];

            omap_l4_io_writeb_fn[i] = omap_l4_io_entry[iotype].mem_write[0];

            omap_l4_io_writeh_fn[i] = omap_l4_io_entry[iotype].mem_write[1];

            omap_l4_io_writew_fn[i] = omap_l4_io_entry[iotype].mem_write[2];

            omap_l4_io_opaque[i] = omap_l4_io_entry[iotype].opaque;

        }


    }



    return base;

}
