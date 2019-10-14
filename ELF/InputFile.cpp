#include "InputFile.h"
#include "Memory.h"
#include <llvm/Object/ELF.h>
#include <llvm/Support/Endian.h>
#include <llvm/Support/ErrorHandling.h>

using namespace llvm;
using namespace llvm::object;

using namespace plastic;
using namespace plastic::elf;

llvm::Optional<MemoryBufferRef> elf::readFile(StringRef Path)
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

InputFile::InputFile(FKind k, MemoryBufferRef M) : ClassKind(k), MBR(M) {}

// TODO: Determine other ELFKind beside ELF64LEKind
template<typename ELFT>
ELFFileBase<ELFT>::ELFFileBase(FKind k, MemoryBufferRef M)
    : InputFile(k, M)
{
    if (ELFT::TargetEndianness == llvm::support::little)
        this->Ekind = ELFT::Is64Bits ? ELFKind::ELF64LE : ELFKind::ELF32LE;
    else
        this->Ekind = ELFT::Is64Bits ? ELFKind::ELF64BE : ELFKind::ELF32BE;

}

template<typename ELFT>
ObjFile<ELFT>::ObjFile(MemoryBufferRef MBR)
    : ELFFileBase<ELFT>(InputFile::FKind::Object, MBR) {}

// TODO: Determine other ELFKind beside ELF64LEKind
// Visible only to this file since it's only used in this file.
static ELFKind getELFKind(MemoryBufferRef MBR)
{
    // EI_CLASS and EI_DATA
    //std::tie(Sz, Endian) = llvm::object::getElfArchType(MBR.getBuffer());
    auto [Sz, Endian]  = llvm::object::getElfArchType(MBR.getBuffer());

    if (Sz == ELF::ELFCLASS64)
        return (Endian == ELF::ELFDATA2LSB) ? ELFKind::ELF64LE : ELFKind::ELF64BE;
    return (Endian == ELF::ELFDATA2LSB) ? ELFKind::ELF32LE : ELFKind::ELF32BE;
}

InputFile *elf::createObjectFile(MemoryBufferRef MBR)
{
    switch (getELFKind(MBR))
    {
    case ELFKind::ELF64LE:
        return make<ObjFile<llvm::object::ELF64LE>>(MBR);
    default:
        // llvm macro that acts like a sentinel
        llvm_unreachable("Failed to create ObjectFile");
    }
}

