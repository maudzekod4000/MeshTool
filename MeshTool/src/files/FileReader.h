#ifndef FILE_READER_H
#define FILE_READER_H

#include <string>

/// <summary>
/// Loads file's contents as text and keeps them as long as FileReader's lifetime.
/// </summary>
class FileReader {
public:

	/// <summary>
	/// Loads and stores the contents of the file in a field.
	/// </summary>
	/// <param name="path">Path to the file</param>
	/// <returns>Flag to indicate whether operation was successful.</returns>
	bool load(std::string path);

	const std::string& getText() const;

	~FileReader() = default;
private:
	std::string text;
};

#endif