#ifndef SRC_GPIO_LED_H_
#define SRC_GPIO_LED_H_

#include "xil_types.h"
#include "xgpio.h"

class Led {
private:
    XGpio gpio;
    XGpio *p_gpio;
public:
    Led();
    ~Led();
    int init(u16 device_id);
    int set(u32 data);
};


#endif /* SRC_GPIO_LED_H_ */
