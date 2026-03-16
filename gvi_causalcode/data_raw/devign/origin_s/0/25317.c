static void gt64120_write_config(PCIDevice *d, uint32_t address, uint32_t val,

                                 int len)

{


    val = bswap32(val);


    pci_default_write_config(d, address, val, len);

}
