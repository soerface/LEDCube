#include "LEDCube.h"

namespace Cube {

    LEDCube::LEDCube() {
        DDRA = 0x1F;
        DDRB = 0x1F;
        DDRD = 0x1F;
    }

    int LEDCube::Clear() {
        for (int i=0; i<5; i++) {
            for (int j=0; j<5; j++) {
                data_buf[i][j] = 0x00;
            }
        }
        return 0;
    }

    int LEDCube::Draw() {
        for (int Layer=0; Layer<5; Layer++) {
            // generate pattern for one layer
            for (int Row=0; Row<5; Row++) {
                PORTD = 1 << Row;
                PORTA = data[Row][Layer];
            }
            // show the layer for a short period of time
            PORTB = 1 << Layer;
            _delay_ms(2);
            PORTB = 0x00;
        }
        return 0;
    }

    int LEDCube::SetLayer(int layer, bool state) {
        for (int i=0; i<5; i++) {
            data_buf[i][layer] = state ? 0x1F : 0x00;
        }
        return 0;
    }

    int LEDCube::SetPixel(int x, int y, int z, bool state) {
        if (x > 4 || y > 4 || z > 4) {
            return -1;
        }
        if (state) {
            data_buf[x][y] |= 1 << z;
        } else {
            data_buf[x][y] &= ~(1 << z);
        }
        return 0;
    }

    int LEDCube::SetPixel(int layer, int pos, bool state) {
        if (layer > 4 || pos > 24) {
            return -1;
        }
        int x = pos % 5;
        int z = pos / 5;
        return SetPixel(x, layer, z, state);
    }

    int LEDCube::Shift(int x, int y, int z) {
        /*
        if (x < -5 || y < -5 || z < -5 ||
            x > 5 || y > 5 || z > 5) {
            return -1;
        }
        */
        if (x < 0) {
            x = 5 + x;
        }
        if (y < 0) {
            y = 5 + y;
        }
        if (z < 0) {
            z = 5 + z;
        }
        for (int i=0; i<5; i++) {
            for (int j=0; j<5; j++) {
                for (int k=0; k<5; k++) {
                    int pattern = data_buf[i][j];
                    for (int l=0; l<z; l++) {
                        int tmp = (pattern & 0x10) >> 4;
                        pattern = pattern << 1;
                        pattern |= tmp;
                    }
                    data[(i + x) % 5][(j + y) % 5] = pattern;
                }
            }
        }
        memcpy(data_buf, data, sizeof(data));
        return 0;
    }

    int LEDCube::Show() {
        memcpy(data, data_buf, sizeof(data));
        return 0;
    }
}
