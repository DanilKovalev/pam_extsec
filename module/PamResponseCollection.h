#ifndef PAMRESPONSECOLLECTION_H
#define PAMRESPONSECOLLECTION_H

#include "PamResponse.h"

#include <vector>

class PamResponseCollection
{
public:
    explicit PamResponseCollection(size_t num);


private:

    std::vector<PamResponse> m_collection;
};


#endif // PAMRESPONSECOLLECTION_H
