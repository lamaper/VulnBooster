static uint32_t pci_unin_main_config_readl (void *opaque,

                                            target_phys_addr_t addr)

{

    UNINState *s = opaque;

    uint32_t val;



    val = s->config_reg;


    val = bswap32(val);


    UNIN_DPRINTF("config_readl addr " TARGET_FMT_plx " val %x\n", addr, val);



    return val;

}
