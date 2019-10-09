#include "LLVM.h"
#include "llvm/Option/ArgList.h"
#include "llvm/ADT/StringRef.h"

namespace plastic
{
namespace elf
{
/*
 * A driver that process command line argument and reading files
 */
class LinkerDriver
{
public:
    void main(ArrayRef<const char *> Args);
    void addFile(StringRef Path, bool WithOption);

};
} // namespace elf
} // namespace plastic
