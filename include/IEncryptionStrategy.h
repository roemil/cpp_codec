#ifndef IENCSTRAT_H
#define IENCSTRAT_H

#include <vector>
#include <cstddef>

class IEncryptionStrategy
{
    public:
        virtual std::string encode(const std::string& plainText) = 0;
        virtual std::string decode(const std::string& encodedText) = 0;

        virtual ~IEncryptionStrategy() = default;
};

#endif