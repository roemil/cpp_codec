#ifndef IENCSTRAT_H
#define IENCSTRAT_H

#include <vector>
#include <cstddef>

using ByteVector = std::vector<std::byte>;

class IEncryptionStrategy
{
    public:
        virtual ByteVector encode(const ByteVector& plainText) = 0;
        virtual ByteVector decode(const ByteVector& encodedText) = 0;

        virtual ~IEncryptionStrategy() = default;
};

#endif