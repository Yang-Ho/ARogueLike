#ifndef CONFIG_H_
#define CONFIG_H_

struct dimensions {
    int width;
    int height;
};

namespace view {
    extern dimensions map;
    extern dimensions info;
    extern dimensions message;
}

#endif
