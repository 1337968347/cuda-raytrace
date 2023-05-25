#include "pbrt.h"

class ReferenceCounted {
   private:
    ReferenceCounted(const ReferenceCounted&);
    ReferenceCounted& operator=(const ReferenceCounted&);
    /* data */
   public:
    int nReferences;
    ReferenceCounted() { nReferences = 0; };
};

template <typename T>
class Reference {
   public:
    Reference(T* p = NULL){};
};