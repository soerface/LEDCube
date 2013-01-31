#define F_CPU 1000000
#include <string.h>
#include <avr/io.h>
#include <util/delay.h>

namespace Cube {

    class LEDCube {

        public:
            LEDCube();
            int Clear();
            int Draw();
            //int Normalize(int &x, int &y, int &z);
            int SetLayer(int layer, bool state=true);
            int SetPixel(int x, int y, int z, bool state=true);
            int SetPixel(int layer, int pos, bool state=true);
            int SetPixel(int pos, bool state=true);
            int Shift(int x, int y, int z);
            int Show();

        private:
            uint8_t data_buf[5][5] = {{0},{0},{0},{0},{0}};
            uint8_t data[5][5] = {{0},{0},{0},{0},{0}};

    };
}
