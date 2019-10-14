#pragma once

#include <llvm/DebugInfo/DWARF/DWARFFormValue.h>
#include <memory>
#include <string>
#include <cstdint>
#include <vector>
#include "LLVM.h"
#include "llvm/ADT/ArrayRef.h"
#include "llvm/Object/ELF.h"
#include "llvm/Support/MemoryBuffer.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/DebugInfo/DWARF/DWARFDebugLine.h"


namespace plastic
{
namespace elf
{

    llvm::Optional<MemoryBufferRef> readFile(StringRef Path);

    enum class ELFKind : uint8_t 
    {
      ELFNone,
      ELF32LE,
      ELF32BE,
      ELF64LE,
      ELF64BE,
    };

    class Symbol;
    class Section;

    class InputFile
    {
    protected:
        // The type of InputFile, used  to destinguish between base class
        // and derived classes.
        enum class FKind : uint8_t
        {
            None,
            Object,
            SharedObject,
            Archive,
        };

    private:
        const FKind ClassKind;
    protected:
        std::vector<Symbol *> Symbols;
    public:
        // Storing the reference to the MB but not owning it
        MemoryBufferRef MBR;
        // Storage for architecture-specific type. i.e. ELF32LE
        ELFKind Ekind = ELFKind::ELFNone;
        // Storage for Machine type, e_type has a size of 2 bytes.
        uint16_t EMKind = llvm::ELF::EM_NONE;

    protected:
        InputFile(FKind k, MemoryBufferRef M);
        llvm::StringRef getName() const { return MBR.getBufferIdentifier(); };
        FKind Kind() const { return this->ClassKind; };
    };

    // ELFT are types defined in llvm/include/llvm/Object/ELFTypes.h. i.e. ELF32LE
    template<typename ELFT>
    class ELFFileBase : public InputFile
    {
    public:
        using Elf_Shdr = typename ELFT::Shdr;
        using Elf_Sym = typename ELFT::Sym;
    protected:
        std::vector<Elf_Sym> SymTables;

    protected:
        ELFFileBase(FKind k, MemoryBufferRef M);
    private:
        // Maps buffer into the object::ELFfile class
        llvm::object::ELFFile<ELFT> getObj() const
        {
            return llvm::object::ELFFile<ELFT>::create(MBR.getBuffer());
        }
    };

    template<typename ELFT>
    class ObjFile : public ELFFileBase<ELFT>
    {
    public:
        using Base = ELFFileBase<ELFT>;
    private:
        // Debug info for retrieving line information
        //std::unique_ptr<llvm::DWARFContext> Dwarf;

    public:
        ObjFile(MemoryBufferRef M);
    };

    InputFile *createObjectFile(MemoryBufferRef MBR);

} // namespace plastic::elf
} // namespace Plastic

