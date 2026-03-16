void alpha_pci_vga_setup(PCIBus *pci_bus)

{

    switch (vga_interface_type) {


    case VGA_QXL:

        pci_create_simple(pci_bus, -1, "qxl-vga");

        return;


    case VGA_CIRRUS:

        pci_cirrus_vga_init(pci_bus);

        return;

    case VGA_VMWARE:

        if (pci_vmsvga_init(pci_bus)) {

            return;

        }

        break;

    }

     

    if (vga_interface_type != VGA_NONE) {

        pci_vga_init(pci_bus);

    }

}
