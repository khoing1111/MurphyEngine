#pragma once

#include "Core.h"
#include "Murphy/IO/MouseEvents.h"

namespace Murphy::Input
{
    MURPHY_API bool IsMousePressed(IO::Mouse::Button& button);
}
