#pragma once

#include<string>
#include<filesystem>

#include"sge_api.h"

namespace SGE{

//Provides functionallity to the game developed via an engine
std::filesystem::path SGE_API GetExecDir();

}
