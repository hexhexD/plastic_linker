#include <memory>
#include "InputFile.h"
#include "Memory.h"

using namespace plastic;

llvm::Optional<MemoryBufferRef> plastic::readFile(StringRef Path)
{
    auto MBOrErr = MemoryBuffer::getFile(Path, -1, false);
    if (auto Err = MBOrErr.getError())
    {
        return {};
    }

    // Get the underlying value when there's no error.
    std::unique_ptr<MemoryBuffer> &MB = *MBOrErr;
    MemoryBufferRef MBRef = MB->getMemBufferRef();

    // Get the ownership of the smart pointer so it doesn't get deleted after
    // this function call
    make<std::unique_ptr<MemoryBuffer>>(std::move(MB));

    return MBRef;
};

