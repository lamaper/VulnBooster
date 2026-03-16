static void pcnet_aprom_writeb(void *opaque, uint32_t addr, uint32_t val)

{

    PCNetState *s = opaque;


    printf("pcnet_aprom_writeb addr=0x%08x val=0x%02x\n", addr, val);


     

    if (pcnet_bcr_readw(s,2) & 0x100)

        s->prom[addr & 15] = val;

}
