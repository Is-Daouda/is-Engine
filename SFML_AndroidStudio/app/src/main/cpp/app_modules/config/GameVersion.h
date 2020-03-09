#ifndef GAME_VERSION_H
#define GAME_VERSION_H

namespace is
{
namespace GameVersion
{
	// version
	static const std::string MAJOR = "1";
	static const std::string MINOR = "0";

	static std::string getGameVersion()
	{
	    return MAJOR + "." + MINOR;
	}
}
}
#endif //GAME_VERSION_H
