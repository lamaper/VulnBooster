void boot_sector_test(void)

{

    uint8_t signature_low;

    uint8_t signature_high;

    uint16_t signature;

    int i;





     

    for (i = 0; i < TEST_CYCLES; ++i) {

        signature_low = readb(BOOT_SECTOR_ADDRESS + SIGNATURE_OFFSET);

        signature_high = readb(BOOT_SECTOR_ADDRESS + SIGNATURE_OFFSET + 1);

        signature = (signature_high << 8) | signature_low;

        if (signature == SIGNATURE) {

            break;

        }

        g_usleep(TEST_DELAY);

    }



    g_assert_cmphex(signature, ==, SIGNATURE);

}
