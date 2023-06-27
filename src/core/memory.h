#include "pbrt.h"
#include "parrallel.h"

class ReferenceCounted
{
public:
    ReferenceCounted() { nReferences = 0; }
    AtomicInt32 nReferences;

private:
    ReferenceCounted(const ReferenceCounted &);
    ReferenceCounted &operator=(const ReferenceCounted &);
};


template <typename T> class Reference {
public: 
    Reference(){

    };

private:
    T *ptr;
};