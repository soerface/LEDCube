#include "main.h"

bool init = false;

int main(void) {
    //TCCR0 |= (1<<CS00);
    //TIMSK |= (1<<TOIE0);
    //TCNT0 = 0;

    //// enable global interrupts
    //sei();

    Cube::LEDCube cube;

    cube.Show();

    int frame = 0;
    int current_animation = 0;
    int animation_counter = 0;
    int (*animations[8]) (Cube::LEDCube &cube) = {
        animation_top_down2,
        animation_top_down,
        animation_blink,
        animation_run,
        animation_sparkles,
        animation_wireframe,
        animation_tetris,
        animation_rain,
    };
    int animation_delays[8] = {4, 5, 100, 5, 40, 40, 30, 25};
    while(1) {
        frame++;
        frame = frame % animation_delays[current_animation];
        if (!frame) {
            animations[current_animation](cube);
            animation_counter++;
            animation_counter %= (2500 / animation_delays[current_animation]);
            if (!animation_counter) {
                current_animation++;
                current_animation %= 7;
                init = false;
                cube.Clear();
                cube.Show();
            }
        }
        cube.Draw();
    }
}

int shuffle(int data[], int size) {
    for (int i=0; i<25; i++) {
        int pos1 = rand() % size;
        int pos2 = rand() % size;
        int tmp = data[pos1];
        data[pos1] = data[pos2];
        data[pos2] = tmp;
    }
}

int animation_blink(Cube::LEDCube &cube) {
    static bool state = true;
    if (state) {
        for (int i=0; i<5; i++) {
            cube.SetLayer(i);
        }
    } else {
        cube.Clear();
    }
    state ^= 1;
    cube.Show();
}

int animation_rain(Cube::LEDCube &cube) {
    cube.SetLayer(4, false);
    cube.Shift(0, 1, 0);
    int i = rand() % 25;
    cube.SetPixel(i);
    cube.Show();
    return 0;
}

int animation_run(Cube::LEDCube &cube) {
    static int pos = 0;
    cube.Clear();
    cube.SetPixel(pos % 125);
    //cube.SetPixel((pos - 1) % 125, false);
    pos++;
    cube.Show();
}

int animation_sparkles(Cube::LEDCube &cube) {
    static int start;
    static int end;
    if (!init) {
        start = 0;
        end = 5;
        init = true;
    }
    cube.Clear();
    for (int i=start % 5; i<end; i+=3) {
        cube.SetPixel(i);
    }
    start++;
    end += 5;
    if (end > 125) {
        end = 125;
    }
    cube.Show();
}

int animation_tetris(Cube::LEDCube &cube) {
    for (int layer=4; layer>0; layer--) {
        for (int i=0; i<25; i++) {
            if (cube.GetPixel(layer-1, i) && !cube.GetPixel(layer, i)) {
                cube.SetPixel(layer, i);
                cube.SetPixel(layer-1, i, false);
            }
            cube.Draw();
        }
    }
    cube.SetPixel(0, rand() % 25);
    cube.Show();
    return 0;
}

int animation_top_down(Cube::LEDCube &cube) {
    static int pixels[2][25];
    static int counter;
    static int delay;
    static int index;
    static bool dir;
    if (!init) {
        dir = true;
        index = 0;
        counter = 0;
        delay = 10;
        cube.SetLayer(0);
        cube.SetLayer(4);
        int layer_counter[2] = {0, 0};
        for (int i=0; i<25; i++) {
            int layer = rand() % 2;
            cube.SetPixel(layer ? 0 : 4, i, false);
            pixels[layer][layer_counter[layer]] = i;
            layer_counter[layer]++;
        }
        cube.Show();
        init = true;
    }
    int pixel = pixels[dir ? 0 : 1][index];
    if (delay) {
        delay--;
        return 0;
    }
    if (dir) {
        cube.SetPixel(counter, pixel, false);
        counter++;
        cube.SetPixel(counter, pixel, true);
    } else {
        cube.SetPixel(4 - counter, pixel, false);
        counter++;
        cube.SetPixel(4 - counter, pixel, true);
    }
    cube.Show();
    if (counter == 4) {
        pixels[dir ? 1 : 0][index] = pixel;
        index++;
        index %= 11;
        counter = 0;
        dir = !dir;
        delay = 10;
    }
    return 0;
}

int animation_top_down2(Cube::LEDCube &cube) {
    static bool dir;
    static int counter;
    static int delay;
    static int data[25];
    static int index;
    if (!init) {
        counter = 0;
        delay = 10;
        dir = false;
        cube.SetLayer(4);
        index = 0;
        for (int i=0; i<25; i++) {
            data[i] = i;
        }
        shuffle(data, 25);
        init = true;
    }
    if (delay) {
        delay--;
        return 0;
    }
    if (dir) {
        cube.SetPixel(counter, data[index], false);
        counter++;
        cube.SetPixel(counter, data[index], true);
    } else {
        cube.SetPixel(4 - counter, data[index], false);
        counter++;
        cube.SetPixel(4 - counter, data[index], true);
    }
    if (counter == 4) {
        index++;
        counter = 0;
        if (index == 25) {
            delay = 20;
            index = 0;
            shuffle(data, 25);
            dir = !dir;
        }
    }
    cube.Show();
    return 0;
}

int animation_wireframe(Cube::LEDCube &cube) {
    static int posx;
    static int posy;
    static int posz;
    static int dirx;
    static int diry;
    static int dirz;
    static int counter;
    if (!init) {
        posx = 0;
        posy = 0;
        posz = 0;
        dirx = 1;
        diry = 0;
        dirz = 0;
        counter = 0;
        init = true;
    }
    if (counter < 25) {
        cube.SetPixel(posx, posy, posz);
        cube.SetPixel(4 - posx, 4 - posy, 4 - posz);
    }
    posx += dirx;
    posy += diry;
    posz += dirz;
    if (counter > 27) {
        for (int i=1; i<4; i++) {
            cube.SetPixel((counter % 4), i, 0, false);
            cube.SetPixel((counter + 1) % 4, i, 0, true);

            cube.SetPixel(4 - (counter % 4), i, 4, false);
            cube.SetPixel(4 - ((counter + 1) % 4), i, 4, true);

            cube.SetPixel(4, i, counter % 4, false);
            cube.SetPixel(4, i, (counter + 1) % 4, true);

            cube.SetPixel(0, i, 4 - (counter % 4), false);
            cube.SetPixel(0, i, 4 - ((counter + 1) % 4), true);
        }
    } else if (posx == 0 && posy == 0 && posz == 0) {
        dirx = 0;
        diry = 1;
        dirz = 0;
    } else if (posx == 4 && posy == 0 && posz == 0) {
        dirx = 0;
        diry = 0;
        dirz = 1;
    } else if (posx == 4 && posy == 0 && posz == 4) {
        dirx = -1;
        diry = 0;
        dirz = 0;
    } else if (posx == 0 && posy == 0 && posz == 4) {
        dirx = 0;
        diry = 0;
        dirz = -1;
    } else if (posx == 0 && posy == 4 && posz == 0) {
        dirx = 0;
        diry = -1;
        dirz = 0;
        posx = 4;
        posy = 4;
        posz = 0;
    }
    counter++;
    cube.Show();
    return 0;
}

ISR(TIMER0_OVF_vect) {
}
