#include <string>
#include "llvm/Object/ELF.h"

namespace plastic 
{
    class Symbol
    {

    };

    class InputFile 
    {
    public:
        InputFile(std::string path);

    private:
        std::string path;
    };

} // namespace Plastic
