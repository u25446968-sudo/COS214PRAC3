#include "Subject.h"

Subject::~Subject(){}

void Subject::attach(Observer* obs){
    for(int i = 0; i < observerList.size(); i++){
        if(observerList[i] == obs){
            return;
        }else{
            observerList.push_back(obs);
        }
    }
}

void Subject::detach(Observer* obs){
    for(int i = 0; i < observerList.size(); i++){
        if(observerList[i] == obs){
            observerList.erase(observerList.begin + i);
        }
    }
}

void Subject::notify(const Notify& notice)const{
    for(Observer* observers: observerList){
        observers->update(notice);
    }
}
