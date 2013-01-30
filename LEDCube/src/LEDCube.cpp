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
                PORTA = data[Layer][Row];
            }
            // show the layer for a short period of time
            PORTB = 1 << Layer;
            _delay_ms(2);
            PORTB = 0x00;
        }
        PORTB = 0x00;
        return 0;
    }

    int LEDCube::SetLayer(int layer) {
        for (int i=0; i<5; i++) {
            data_buf[layer][i] = 0x1F;
        }
        return 0;
    }

    int LEDCube::SetPixel(int x, int y, int z, bool state) {
        if (x > 4 || y > 4 || z > 4) {
            return -1;
        }
        if (state) {
            data_buf[y][x] |= 1 << z;
        } else {
            data_buf[y][x] &= ~(1 << z);
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

    int LEDCube::Show() {
        memcpy(data, data_buf, sizeof(data));
        return 0;
    }
}
