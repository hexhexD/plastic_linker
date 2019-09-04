#include "InputFile.h"

using namespace plastic;
using namespace plastic::elf;

llvm::Optional<MemoryBufferRef> elf::readFile(StringRef path)
{
    auto MBOrErr = MemoryBuffer::getFile(path, -1, false);
    if (auto Err = MBOrErr.getError())
    {
        return {};
    }

    // Get the underlying value when there's no error.
    std::unique_ptr<MemoryBuffer> &MB = *MBOrErr;
    MemoryBufferRef MBRef = MB->getMemBufferRef();

    return MBRef;
};

