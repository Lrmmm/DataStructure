#include<mutex>
#include<iostream>
using namespace std;

namespace lrm{
template <class T>
class shared_ptr{
public:
    shared_ptr(T* ptr):_ptr(ptr),_pcount(new int(1)),_pmtx(new mutex()){
        if(ptr == NULL) *(_pcount) = 0;
    };
    shared_ptr(const shared_ptr<T> &sp):
        _ptr(sp._ptr),
        _pcount(sp._pcount),
        _pmtx(sp._pmtx){
        AddCount();
    }

    shared_ptr& operator=(const shared_ptr<T>& sp){
        if (_ptr != sp._ptr){
            Release();
            _ptr = sp._ptr;
            _pcount = sp._pcount;
            _pmtx = sp._pmtx;
            AddCount();
        }
        return *this;
    }

    void Release(){
        _pmtx->lock();
        bool DeleteFlag = false;

        if (--(*_pcount) == 0)
        {
            cout << "delete" << ":" << _ptr << endl;
            delete _ptr;
            delete _pcount;
            DeleteFlag = true;
        }
        _pmtx->unlock();

        if (DeleteFlag == true)
            delete _pmtx;
    }
    void AddCount(){
        _pmtx->lock();
        ++(*_pcount);
        _pmtx->unlock();
    }

    ~shared_ptr(){
        Release();
    }

    T& operator*(){
        return *_ptr;
    }

    T* operator->(){
        return _ptr;
    }

    int userCount(){
        return *(_pcount);
    }

private:
    T *_ptr;
    int* _pcount;
    mutex *_pmtx;
};
}
