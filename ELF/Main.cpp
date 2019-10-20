#include <vector>
#include <string>
#include "llvm/Object/ELF.h"
#include "llvm/Support/Path.h"
#include "llvm/ADT/StringRef.h"
#include "InputFile.h"
#include "Memory.h"
#include "Driver.h"

using namespace plastic;
using namespace llvm;


int main(int argc, char **argv)
{

    // Construct vector using iterator
    std::vector<const char *> Args(argv, argv + argc);

    elf::link(Args);

    //Optional<MemoryBufferRef> MBROrNone = elf::readFile("../tests/main.o");
    //if (!MBROrNone.hasValue())
        //return 1;
    //MemoryBufferRef Ref = *MBROrNone;
    //outs() << Ref.getBufferIdentifier();
    //elf::InputFile *k = elf::createObjectFile(Ref);

    //std::vector<int> a;
    //make<std::vector<int>>(a);

    freeArena();
}
