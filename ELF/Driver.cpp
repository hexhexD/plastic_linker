#include <filesystem>
#include <vector>
#include "Driver.h"
#include "LLVM.h"
#include "Memory.h"
#include "InputFile.h"
#include <llvm/ADT/ArrayRef.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/BinaryFormat/Magic.h>
#include <llvm/Support/ErrorHandling.h>

using namespace plastic;
using namespace plastic::elf;

namespace fs = std::filesystem;

LinkerDriver *elf::Driver;

bool elf::link(ArrayRef<const char *> Args)
{
    Driver = make<LinkerDriver>();

    Driver->main(Args);
    return true;
}

void LinkerDriver::main(ArrayRef<const char *> Args)
{
    Args = Args.slice(1);

    std::vector<std::string> PathArr;

    for (auto e : Args)
    {
        fs::path p = e;
        PathArr.push_back(fs::canonical(p).string());
    }

    createFiles(PathArr);
}

void LinkerDriver::createFiles(ArrayRef<std::string> PathArr)
{
    for (auto e : PathArr)
        addFile(e);
}

void LinkerDriver::addFile(StringRef Path)
{
    llvm::Optional<MemoryBufferRef> ErrorOr = readFile(Path);

    MemoryBufferRef MBR = *ErrorOr;

    switch(llvm::identify_magic(MBR.getBuffer()))
    {
    case llvm::file_magic::elf_relocatable:
        this->Files.push_back(createObjectFile(MBR));
        break;
    default:
        llvm_unreachable("Failed to identify magic");
    }
}
