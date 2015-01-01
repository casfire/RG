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

void TextTokenizer::load(Storage &storage, std::istream &stream)
{
	loadBegin(storage);
	stream.exceptions(stream.exceptions() & ~std::istream::failbit);
	for (std::string line; std::getline(stream, line); ) {
		
		std::size_t length = static_cast<std::size_t>(line.size());
		std::size_t pos = 0;
		
		/* Copy line */
		std::vector<char> copy(line.size() + 1);
		for (std::size_t i = 0; i < length; i++) copy[i] = line[i];
		copy[length] = '\0';
		char* s = copy.data();
		
		/* Remove comment */
		for (std::size_t i = 0; i < length; i++) {
			if (s[i] == '#') {
				length = i;
				s[i] = '\0';
			}
		}
	
		/* Skip spaces and non-printable characters */
		while (pos < length && !std::isgraph(s[pos])) pos++;
		
		/* Retreive first token */
		std::size_t start = pos;
		while (pos < length && std::isgraph(s[pos])) pos++;
		if (pos <= start) continue;
		std::string t(static_cast<const char*>(s + start), pos - start);
		
		/* Skip spaces and non-printable characters */
		while (pos < length && !std::isgraph(s[pos])) pos++;
		
		/* Call virtual token method */
		loadToken(storage, t, std::string(static_cast<const char*>(s + pos)));
		
	}
	loadEnd(storage);
}
