#ifndef CLICKER_CLICKER_H
#define CLICKER_CLICKER_H

namespace clicker {

    inline int upscale = 0;
    inline char bind = 0;

    inline bool enable = false;
    inline bool inventory = false;
    inline bool rmb_lock = false;

    extern void thread();
    extern void binds();

}

#endif //CLICKER_CLICKER_H
