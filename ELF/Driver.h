#include "InputFile.h"
#include "LLVM.h"
#include "llvm/Option/ArgList.h"
#include "llvm/ADT/StringRef.h"
#include <vector>

namespace plastic
{

namespace elf 
{
    bool link(llvm::ArrayRef<const char *> Args);
} // namespace elf

namespace elf
{

class LinkerDriver;
extern LinkerDriver *Driver;
/*
 * A driver that process command line argument and reading files
 */
class LinkerDriver
{
private:
    std::vector<InputFile *> Files;
public:
    // Accept a list of file for now
    void main(ArrayRef<const char *> Args);
private:
    void createFiles(ArrayRef<std::string> PathArr);
    void addFile(StringRef Path);
};

} // namespace elf
} // namespace plastic
