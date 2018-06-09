#ifndef DEVICE_ACTION_HPP
#define DEVICE_ACTION_HPP

struct device_action
{
    int power;  // 0-no action; <0-decrease power; >0-increase;
    int fan;    // 0-no action; <0-decrease rpm; >0-increase;
};

#endif /* DEVICE_ACTION_HPP */

