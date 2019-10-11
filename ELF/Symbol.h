#pragma once 

#include "LLVM.h"
#include "llvm/Object/ELF.h"
#include "llvm/ADT/StringRef.h"

namespace plastic
{
namespace elf
{
class InputFile;
class SectionBase;
} // namespace elf

namespace elf
{
// Base class of symbol
class Symbol
{
protected:
    enum Kind
    {
        PlaceolderKind,
        DefinedKind,
        UndefinedKind,
        LazyObjectKind,
    };

private:
    Kind SymbolKind;
    InputFile *File;
protected:
    // Name in string table
    const char *Name;
    uint8_t Type;       // st_info
    uint8_t StOther;    // st_other

protected:
    Symbol(Kind K, InputFile *File, StringRef Name, 
           uint8_t Type, uint8_t StOther)
        : SymbolKind(K), File(File), Type(Type), StOther(StOther) {}
};

class Defined : public Symbol
{
private:
    uint64_t Value; // st_value
    uint64_t Size;  // st_size
    // Which section this symbol is from
    SectionBase *Section;
public:
    Defined(InputFile *File, StringRef Name, 
           uint8_t Type, uint8_t StOther, uint64_t Value, uint64_t Size,
           SectionBase *Section)
        : Symbol(DefinedKind, File, Name, Type, StOther), Value(Value), Size(Size), 
          Section(Section) {}
};

class Undefined : public Symbol
{
public:
    Undefined(InputFile *File, StringRef Name,uint8_t Type, uint8_t StOther)
        : Symbol(UndefinedKind, File, Name, Type, StOther) {}
};

} // namespace elf
} // namespace plastic
