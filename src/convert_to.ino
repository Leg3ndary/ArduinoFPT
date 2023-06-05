int* convert(int leds[]) {
    int result[] = {0, 0, 0, 0};
    
    int binary[4][7] = {
        {0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0},
    };

    for (int i = 0; i < sizeof(leds) / sizeof(leds[0]); i++) {
        int bitShifter = leds[i] / 7;
        int bit = leds[i] % 7;
        binary[bitShifter][bit] = 1;
    }

    for (int i = 0; i < 4; i++) {
        int decimal = 0;
        for(int j = 0 ; j < 8 ; j++) {
            decimal = (decimal << 1) + binary[i][j];
        }
        result[i] = decimal;
    }
    
    return result;
}