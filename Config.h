#ifndef CONFIG_H
#define CONFIG_H

struct point {
    int x;
    int y;
};

typedef point type_el;

const unsigned char POISON_BYTE = 0xbe;
type_el make_poison_el();
const type_el POISON_EL = make_poison_el();

#define type_el_print "x = %d, y = %d"
#define el_print(value) value.x, value.y

#endif // CONFIG_H