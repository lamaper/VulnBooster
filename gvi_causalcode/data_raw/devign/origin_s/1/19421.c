static int assigned_device_pci_cap_init(PCIDevice *pci_dev)

{

    AssignedDevice *dev = DO_UPCAST(AssignedDevice, dev, pci_dev);

    PCIRegion *pci_region = dev->real_device.regions;

    int ret, pos;



     

    pci_set_byte(pci_dev->config + PCI_CAPABILITY_LIST, 0);

    pci_set_word(pci_dev->config + PCI_STATUS,

                 pci_get_word(pci_dev->config + PCI_STATUS) &

                 ~PCI_STATUS_CAP_LIST);



     

    pos = pci_find_cap_offset(pci_dev, PCI_CAP_ID_MSI, 0);

    if (pos != 0 && kvm_check_extension(kvm_state, KVM_CAP_ASSIGN_DEV_IRQ)) {

        if (!check_irqchip_in_kernel()) {

            return -ENOTSUP;

        }

        dev->cap.available |= ASSIGNED_DEVICE_CAP_MSI;

         

        ret = pci_add_capability(pci_dev, PCI_CAP_ID_MSI, pos, 10);

        if (ret < 0) {

            return ret;

        }

        pci_dev->msi_cap = pos;



        pci_set_word(pci_dev->config + pos + PCI_MSI_FLAGS,

                     pci_get_word(pci_dev->config + pos + PCI_MSI_FLAGS) &

                     PCI_MSI_FLAGS_QMASK);

        pci_set_long(pci_dev->config + pos + PCI_MSI_ADDRESS_LO, 0);

        pci_set_word(pci_dev->config + pos + PCI_MSI_DATA_32, 0);



         

        pci_set_word(pci_dev->wmask + pos + PCI_MSI_FLAGS,

                     PCI_MSI_FLAGS_QSIZE | PCI_MSI_FLAGS_ENABLE);

        pci_set_long(pci_dev->wmask + pos + PCI_MSI_ADDRESS_LO, 0xfffffffc);

        pci_set_word(pci_dev->wmask + pos + PCI_MSI_DATA_32, 0xffff);

    }

     

    pos = pci_find_cap_offset(pci_dev, PCI_CAP_ID_MSIX, 0);

    if (pos != 0 && kvm_device_msix_supported(kvm_state)) {

        int bar_nr;

        uint32_t msix_table_entry;



        if (!check_irqchip_in_kernel()) {

            return -ENOTSUP;

        }

        dev->cap.available |= ASSIGNED_DEVICE_CAP_MSIX;

        ret = pci_add_capability(pci_dev, PCI_CAP_ID_MSIX, pos, 12);

        if (ret < 0) {

            return ret;

        }

        pci_dev->msix_cap = pos;



        pci_set_word(pci_dev->config + pos + PCI_MSIX_FLAGS,

                     pci_get_word(pci_dev->config + pos + PCI_MSIX_FLAGS) &

                     PCI_MSIX_FLAGS_QSIZE);



         

        pci_set_word(pci_dev->wmask + pos + PCI_MSIX_FLAGS,

                     PCI_MSIX_FLAGS_ENABLE | PCI_MSIX_FLAGS_MASKALL);



        msix_table_entry = pci_get_long(pci_dev->config + pos + PCI_MSIX_TABLE);

        bar_nr = msix_table_entry & PCI_MSIX_FLAGS_BIRMASK;

        msix_table_entry &= ~PCI_MSIX_FLAGS_BIRMASK;

        dev->msix_table_addr = pci_region[bar_nr].base_addr + msix_table_entry;

        dev->msix_max = pci_get_word(pci_dev->config + pos + PCI_MSIX_FLAGS);

        dev->msix_max &= PCI_MSIX_FLAGS_QSIZE;

        dev->msix_max += 1;

    }



     

    pos = pci_find_cap_offset(pci_dev, PCI_CAP_ID_PM, 0);

    if (pos) {

        uint16_t pmc;



        ret = pci_add_capability(pci_dev, PCI_CAP_ID_PM, pos, PCI_PM_SIZEOF);

        if (ret < 0) {

            return ret;

        }



        assigned_dev_setup_cap_read(dev, pos, PCI_PM_SIZEOF);



        pmc = pci_get_word(pci_dev->config + pos + PCI_CAP_FLAGS);

        pmc &= (PCI_PM_CAP_VER_MASK | PCI_PM_CAP_DSI);

        pci_set_word(pci_dev->config + pos + PCI_CAP_FLAGS, pmc);



         

        pci_set_word(pci_dev->config + pos + PCI_PM_CTRL,

                     PCI_PM_CTRL_NO_SOFT_RESET);



        pci_set_byte(pci_dev->config + pos + PCI_PM_PPB_EXTENSIONS, 0);

        pci_set_byte(pci_dev->config + pos + PCI_PM_DATA_REGISTER, 0);

    }



    pos = pci_find_cap_offset(pci_dev, PCI_CAP_ID_EXP, 0);

    if (pos) {

        uint8_t version, size = 0;

        uint16_t type, devctl, lnksta;

        uint32_t devcap, lnkcap;



        version = pci_get_byte(pci_dev->config + pos + PCI_EXP_FLAGS);

        version &= PCI_EXP_FLAGS_VERS;

        if (version == 1) {

            size = 0x14;

        } else if (version == 2) {

             

            size = MIN(0x3c, PCI_CONFIG_SPACE_SIZE - pos);

            if (size < 0x34) {

                error_report("%s: Invalid size PCIe cap-id 0x%x",

                             __func__, PCI_CAP_ID_EXP);

                return -EINVAL;

            } else if (size != 0x3c) {

                error_report("WARNING, %s: PCIe cap-id 0x%x has "

                             "non-standard size 0x%x; std size should be 0x3c",

                             __func__, PCI_CAP_ID_EXP, size);

            }

        } else if (version == 0) {

            uint16_t vid, did;

            vid = pci_get_word(pci_dev->config + PCI_VENDOR_ID);

            did = pci_get_word(pci_dev->config + PCI_DEVICE_ID);

            if (vid == PCI_VENDOR_ID_INTEL && did == 0x10ed) {

                 

                size = 0x3c;

            }

        }



        if (size == 0) {

            error_report("%s: Unsupported PCI express capability version %d",

                         __func__, version);

            return -EINVAL;

        }



        ret = pci_add_capability(pci_dev, PCI_CAP_ID_EXP, pos, size);

        if (ret < 0) {

            return ret;

        }



        assigned_dev_setup_cap_read(dev, pos, size);



        type = pci_get_word(pci_dev->config + pos + PCI_EXP_FLAGS);

        type = (type & PCI_EXP_FLAGS_TYPE) >> 4;

        if (type != PCI_EXP_TYPE_ENDPOINT &&

            type != PCI_EXP_TYPE_LEG_END && type != PCI_EXP_TYPE_RC_END) {

            error_report("Device assignment only supports endpoint assignment,"

                         " device type %d", type);

            return -EINVAL;

        }



         



         

        devcap = pci_get_long(pci_dev->config + pos + PCI_EXP_DEVCAP);

        devcap &= ~PCI_EXP_DEVCAP_FLR;

        pci_set_long(pci_dev->config + pos + PCI_EXP_DEVCAP, devcap);



         

        devctl = pci_get_word(pci_dev->config + pos + PCI_EXP_DEVCTL);

        devctl = (devctl & (PCI_EXP_DEVCTL_READRQ | PCI_EXP_DEVCTL_PAYLOAD)) |

                  PCI_EXP_DEVCTL_RELAX_EN | PCI_EXP_DEVCTL_NOSNOOP_EN;

        pci_set_word(pci_dev->config + pos + PCI_EXP_DEVCTL, devctl);

        devctl = PCI_EXP_DEVCTL_BCR_FLR | PCI_EXP_DEVCTL_AUX_PME;

        pci_set_word(pci_dev->wmask + pos + PCI_EXP_DEVCTL, ~devctl);



         

        pci_set_word(pci_dev->config + pos + PCI_EXP_DEVSTA, 0);



         

        lnkcap = pci_get_long(pci_dev->config + pos + PCI_EXP_LNKCAP);

        lnkcap &= (PCI_EXP_LNKCAP_SLS | PCI_EXP_LNKCAP_MLW |

                   PCI_EXP_LNKCAP_ASPMS | PCI_EXP_LNKCAP_L0SEL |

                   PCI_EXP_LNKCAP_L1EL);

        pci_set_long(pci_dev->config + pos + PCI_EXP_LNKCAP, lnkcap);



         



         

        lnksta = pci_get_word(pci_dev->config + pos + PCI_EXP_LNKSTA);

        lnksta &= (PCI_EXP_LNKSTA_CLS | PCI_EXP_LNKSTA_NLW);

        pci_set_word(pci_dev->config + pos + PCI_EXP_LNKSTA, lnksta);



        if (version >= 2) {

             

            pci_set_long(pci_dev->config + pos + PCI_EXP_SLTCAP, 0);

            pci_set_word(pci_dev->config + pos + PCI_EXP_SLTCTL, 0);

            pci_set_word(pci_dev->config + pos + PCI_EXP_SLTSTA, 0);



             

            pci_set_word(pci_dev->config + pos + PCI_EXP_RTCTL, 0);

            pci_set_word(pci_dev->config + pos + PCI_EXP_RTCAP, 0);

            pci_set_long(pci_dev->config + pos + PCI_EXP_RTSTA, 0);



             

             

        }

    }



    pos = pci_find_cap_offset(pci_dev, PCI_CAP_ID_PCIX, 0);

    if (pos) {

        uint16_t cmd;

        uint32_t status;



         

        ret = pci_add_capability(pci_dev, PCI_CAP_ID_PCIX, pos, 8);

        if (ret < 0) {

            return ret;

        }



        assigned_dev_setup_cap_read(dev, pos, 8);



         

        cmd = pci_get_word(pci_dev->config + pos + PCI_X_CMD);

        cmd &= (PCI_X_CMD_DPERR_E | PCI_X_CMD_ERO | PCI_X_CMD_MAX_READ |

                PCI_X_CMD_MAX_SPLIT);

        pci_set_word(pci_dev->config + pos + PCI_X_CMD, cmd);



         

        status = pci_get_long(pci_dev->config + pos + PCI_X_STATUS);

        status &= ~(PCI_X_STATUS_BUS | PCI_X_STATUS_DEVFN);

        status |= (pci_bus_num(pci_dev->bus) << 8) | pci_dev->devfn;

        status &= ~(PCI_X_STATUS_SPL_DISC | PCI_X_STATUS_UNX_SPL |

                    PCI_X_STATUS_SPL_ERR);

        pci_set_long(pci_dev->config + pos + PCI_X_STATUS, status);

    }



    pos = pci_find_cap_offset(pci_dev, PCI_CAP_ID_VPD, 0);

    if (pos) {

         

        ret = pci_add_capability(pci_dev, PCI_CAP_ID_VPD, pos, 8);

        if (ret < 0) {

            return ret;

        }



        assigned_dev_setup_cap_read(dev, pos, 8);



         

        assigned_dev_direct_config_write(dev, pos + 2, 6);

    }



     

    for (pos = 0; (pos = pci_find_cap_offset(pci_dev, PCI_CAP_ID_VNDR, pos));

        pos += PCI_CAP_LIST_NEXT) {

        uint8_t len = pci_get_byte(pci_dev->config + pos + PCI_CAP_FLAGS);

         

        ret = pci_add_capability(pci_dev, PCI_CAP_ID_VNDR, pos, len);

        if (ret < 0) {

            return ret;

        }



        assigned_dev_setup_cap_read(dev, pos, len);



         

        assigned_dev_direct_config_write(dev, pos + 2, len - 2);

    }



     

    if ((pci_get_word(pci_dev->config + PCI_STATUS) & PCI_STATUS_CAP_LIST) !=

        (assigned_dev_pci_read_byte(pci_dev, PCI_STATUS) &

         PCI_STATUS_CAP_LIST)) {

        dev->emulate_config_read[PCI_STATUS] |= PCI_STATUS_CAP_LIST;

    }



    return 0;

}
