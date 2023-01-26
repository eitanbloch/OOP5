//
// Created by Eitan Bloch on 23/01/2023.
//

#ifndef OOP5_SUBJECT_H
#define OOP5_SUBJECT_H

#include "Observer.h"
#include "OOP5EventException.h"
#include <vector>

template<typename T>
class Subject {

    std::vector<Observer<T> *> observers;

public:
    Subject() {
        observers = std::vector<Observer<T> *>();
    }

    void notifyObservers(const T& msg) {
        for (auto observer: observers) {
            observer->handleEvent(msg);
        }
    }

    void addObserver(Observer<T>& obs) {
        for (auto observer: observers) {
            if (observer == &obs) {
                throw ObserverAlreadyKnownToSubject();
            }
        }
        observers.push_back(&obs);
    }

    void removeObserver(Observer<T>& obs) {
        for (auto observer: observers) {
            if (observer == &obs) {
                observers.erase(std::remove(observers.begin(), observers.end(), &obs), observers.end());
                return;
            }
        }
        throw ObserverUnknownToSubject();
    }

    Subject<T>& operator+=(Observer<T>& obs) {
        addObserver(obs);
        return *this;
    }

    Subject<T>& operator-=(Observer<T>& obs) {
        removeObserver(obs);
        return *this;
    }

    Subject<T>& operator()(const T& msg) {
        notifyObservers(msg);
        return *this;
    }
};


#endif //OOP5_SUBJECT_H
