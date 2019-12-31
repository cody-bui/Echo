#pragma once

#include <nlohmann/json.hpp>
#include <EchoHeader.h>

using json = nlohmann::json;

json settings = json::parse(
	std::ifstream(std::filesystem::current_path().string() + "/../Echo/src/Settings.json")
);
