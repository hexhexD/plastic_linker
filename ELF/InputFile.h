#pragma once

#include <string>
#include <cstdint>
#include "LLVM.h"
#include "llvm/ADT/ArrayRef.h"
#include "llvm/Object/ELF.h"
#include "llvm/Support/MemoryBuffer.h"
#include "llvm/ADT/StringRef.h"


namespace plastic
{

    llvm::Optional<MemoryBufferRef> readFile(StringRef path);

    enum class ELFKind : uint8_t
    {
        ELFNoneKind,
        ELF32LEKind,
        ELF32BEKind,
        ELF64LEKind,
        ELF64BEKind,
    };

    class Symbol;
    class Section;

    // The base of all input file
    class InputFile
    {
    public:
        // The type of InputFile, used  to destinguish between base class
        // and derived classes.
        enum class Kind : uint8_t
        {
            NoneKind,
            ObjectKind,
            SharedObjectKind,
            ArchiveKind,
        };

    private:
        const Kind NoneKind;

    public:
        // 
        MemoryBufferRef MB;
        // Storage for architecture-specific type. i.e. ELF32LE
        ELFKind Ekind = ELFKind::ELFNoneKind;
        // Storage for Machine type, e_type has a size of 2 bytes.
        uint16_t EMKind = llvm::ELF::EM_NONE;

        //llvm::StringRef getName() const { return MB.getBufferIdentifier(); };

    protected:
        InputFile(Kind k, llvm::MemoryBufferRef M);
    };

    // ELFT are types defined in llvm/include/llvm/Object/ELFTypes.h. i.e. ELF32LE
    template<typename ELFT>
    class ELFFileBase : public InputFile
    {
    public:
        using Elf_Shdr = typename ELFT::Shdr;
        using Elf_Sym = typename ELFT::Sym;

    protected:
        std::vector<Elf_Sym> SymTable;

    public:
        llvm::object::ELFFile<ELFT> getObj() const
        {
            return llvm::object::ELFFile<ELFT>::create(MB.getBuffer());
        }
    };

    class Symbol
    {
    public:
        // The file where the symbol is defined.
        InputFile *File;

        // Storage for symbol type anonymous enum defined in llvm ELF header.
        uint8_t Type;
    };

} // namespace Plastic

