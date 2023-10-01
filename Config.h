#ifndef CONFIG_H
#define CONFIG_H

const unsigned char POISON_BYTE = 0xbe;

struct point {
    int x;
    int y;
};

typedef point type_el;

const type_el POISON_EL = (point){POISON_BYTE, POISON_BYTE};
#define type_el_print "x = %d, y = %d"
#define el_print(value) value.x, value.y

#endif // CONFIG_H