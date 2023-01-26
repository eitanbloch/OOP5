//
// Created by Eitan Bloch on 23/01/2023.
//

#ifndef OOP5_OBSERVER_H
#define OOP5_OBSERVER_H

template <typename T>
class Observer {
public:
    virtual void handleEvent(const T&) = 0;
};




#endif //OOP5_OBSERVER_H
