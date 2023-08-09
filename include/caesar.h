#ifndef CAESAR_H
#define CAESAR_H

#include <vector>
#include <cstddef>
#include "IEncryptionStrategy.h"

using ByteVector = std::vector<std::byte>;
class Caesar : public IEncryptionStrategy
{
private:
    int shift_;

public:
    Caesar(int shift = 3) : shift_ {shift} {};
    ByteVector encode(const ByteVector& PlainText);
    ByteVector decode(const ByteVector& EncryptedString);
};

#endif