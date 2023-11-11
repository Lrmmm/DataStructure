#ifndef __Dictionary__
#define __Dictionary__
template<class K, class V>
class Dictionary{
public:
    virtual ~Dictionary(){}
    virtual bool empty() const = 0;
    virtual int size() const = 0;
    virtual pair<const K, V>* find(const K&) const = 0;
    virtual void erase(const K&) = 0;
    virtual void insert(const pair<const K, V>& ) = 0;
};
#endif