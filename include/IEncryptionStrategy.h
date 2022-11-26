#ifndef IENCSTRAT_H
#define IENCSTRAT_H

#include <string>

class IEncryptionStrategy
{
    public:
        virtual std::string encode(const std::string& plainText) = 0;
        virtual std::string decode(const std::string& encodedText) = 0;

        virtual ~IEncryptionStrategy() = default;
        /*IEncryptionStrategy(const IEncryptionStrategy& other) = default;
        IEncryptionStrategy(IEncryptionStrategy&& other) = default;
        IEncryptionStrategy &operator =(const IEncryptionStrategy &other) = default;*/
};

#endif