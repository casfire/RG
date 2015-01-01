#include "Text.hpp"
#include <cctype> // std::isgraph
#include <cstddef> // std::size_t

using Engine::Asset::TextRaw;
using Engine::Asset::TextTokenizer;

void TextRaw::load(Storage &storage, std::istream &stream)
{
	std::vector<char> contents;
	stream.seekg(0, std::ios_base::end);
	std::streamsize size = stream.tellg();
	stream.seekg(0, std::ios_base::beg);
	contents.resize(static_cast<std::size_t>(size + 1));
	stream.read(contents.data(), size);
	contents[size] = '\0';
	load(storage, contents);
}

inline std::string& inl_ltrim(std::string &s) {
	std::size_t pos = 0;
	while (pos < s.size() && !std::isgraph(s[pos])) pos++;
	return s.erase(0, pos);
}

inline std::string& inl_rtrim(std::string &s) {
	std::size_t pos = s.size();
	while (pos > 0 && !std::isgraph(s[pos - 1])) pos--;
	return s.erase(pos);
}

inline std::string inl_ltoken(const std::string &s) {
	std::size_t pos = 0;
	while (pos < s.size() && std::isgraph(s[pos])) pos++;
	return s.substr(0, pos);
}

void TextTokenizer::load(Storage &storage, std::istream &stream)
{
	loadBegin(storage);
	stream.exceptions(stream.exceptions() & ~std::istream::failbit);
	for (std::string line; std::getline(stream, line); ) {
		
		/* Remove comment */
		std::string::size_type n = line.find('#');
		if (n != std::string::npos) line.erase(n);
		
		/* Left and right trim */
		line = inl_ltrim(inl_rtrim(line));
		
		/* Retreive key */
		std::string key = inl_ltoken(line);
		line.erase(0, key.size());
		
		/* Left trim */
		line = inl_ltrim(line);
		
		/* Call virtual token method */
		loadToken(storage, key, line);
		
	}
	loadEnd(storage);
}
