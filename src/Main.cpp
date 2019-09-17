#include <vector>
#include "llvm/Object/ELF.h"
#include "InputFile.h"
#include "Memory.h"

using namespace plastic;

int main()
{
    llvm::Optional<MemoryBufferRef> MBROrNone = ::readFile("/home/alchemist/workplace/linker_llvm/tests/main.o");
    if (!MBROrNone.hasValue())
        return 1;
    MemoryBufferRef Ref = *MBROrNone;
    llvm::outs() << Ref.getBufferIdentifier();

    std::vector<int> a;
    make<std::vector<int>>(a);

    freeArena();
}
