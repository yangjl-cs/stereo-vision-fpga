#ifndef SRC_DYNCLK_CTRL_DYNCLK_CTRL_H_
#define SRC_DYNCLK_CTRL_DYNCLK_CTRL_H_

typedef enum {
    DYNCLK_STOPPED = 0,
    DYNCLK_RUNNING = 1
} DynclkState;


class DynclkCtrl {
private:
    double pxl_freq;
    u32 base_addr;
    DynclkState state;
public:
    DynclkCtrl();
    ~DynclkCtrl();
    int init(u32 base_addr, const double freq);
    int start(const double freq);
    int stop();
};

#endif /* SRC_DYNCLK_CTRL_DYNCLK_CTRL_H_ */
