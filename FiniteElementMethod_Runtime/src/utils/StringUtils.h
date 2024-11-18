#pragma once

std::vector<std::string> Split(const std::string& str, const char delimiter);

std::string thread_id_to_string(const std::thread::id& id);
