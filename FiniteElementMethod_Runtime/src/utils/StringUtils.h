#pragma once

std::vector<std::string> Split(const std::string& str, const char delimiter);

std::string ThreadIdToString(const std::thread::id& id);
