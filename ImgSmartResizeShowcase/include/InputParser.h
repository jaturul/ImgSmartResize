#include <algorithm>
#include <queue>
#include <string>
#include <vector>
#include <map>

class InputParser
{
public:
	InputParser();
	~InputParser();

	std::vector<std::string> parseInput(int argc, char** argv);

private:
	std::vector<std::string> getRawInput(int argc, char** argv);
	std::string getFilenameFromPath(const std::string& path);

	bool isImageName(const std::string& path);
	bool isAlphanumerical(const std::string& name);
	bool isAcceptableTag(const std::string& tag);
	bool isAcceptableImageExtension(const std::string& extension);
	bool isImageTransformationLabel(const std::string& label);
	bool isNumber(const std::string& number);
	bool isValidSize(const std::string& name);
	bool isValidInput(const std::vector<std::string> input);
	std::string getHeight(const std::string& sizeStr);
	std::string getWidth(const std::string& sizeStr);
	std::string getImageExtension(const std::string& imageName);
	std::string getImageName(const std::string& imageName);

	std::map<std::string, char> m_tagCodes;
};
