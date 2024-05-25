#pragma once

#include <string>

#include "datagram.h"
#include "leychan.h"

void ProcessCommandLine(Datagram*, leychan*, std::string);
void CommandTick(Datagram*, leychan*);