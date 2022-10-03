#include <windows.h>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>
#include <boost/json/src.hpp>

#include "MobConstants.h"
#include "SectorNPCReverser.h"

/**
 Read up to 4 bytes starting from a specified position in a file.

 Note: this method moves the file pointer by a number of bytes read

 @param file - file to read from
 @param start - position in a file to read from inclusively
 @param length - number of bytes to read.
 @returns 4-byte unsigned integer
 */
uint32_t readUpTo4Bytes(std::ifstream& file, const uint32_t start, const uint32_t length) {
	file.seekg(start, std::ios::beg);
	std::vector<uint8_t> container = std::vector<uint8_t>(length);
	file.read(reinterpret_cast<char*>(container.data()), length);
	uint32_t result{};
	memcpy(&result, container.data(), length);
	return result;
}

int main() {
	WIN32_FIND_DATA data;
	const LPCWSTR mapDirRaw = L"e:\\SteamLibrary\\steamapps\\common\\Arcanum\\Arcanum\\modules\\undat\\maps\\Arcanum1-024-fixed\\*";
	const std::wstring wMapDir = std::wstring(mapDirRaw);
	const std::string mapDir = std::string(wMapDir.begin(), wMapDir.end());
	HANDLE hFind = FindFirstFile(mapDirRaw, &data);
	uint16_t mobFilesCount{};
	if (hFind != INVALID_HANDLE_VALUE) {
		boost::json::array npcs;
		do {
			const std::wstring wFileName = std::wstring(data.cFileName);
			const std::string fileName = std::string(wFileName.begin(), wFileName.end());
			if (fileName.find(".mob") != std::string::npos) {
				++mobFilesCount;
				const std::string mobFileAbsPath = mapDir.substr(0, mapDir.length() - 1) + fileName;
				std::ifstream mobFile(mobFileAbsPath, std::ifstream::in);
				if (mobFile.is_open()) {
					const uint32_t columnTileIndex = readUpTo4Bytes(mobFile, MobConstants::ColumnTileIndexOffset, MobConstants::ColumnTileIndexLength);
					const uint32_t rowTileIndex = readUpTo4Bytes(mobFile, MobConstants::RowTileIndexOffset, MobConstants::RowTileIndexLength);
					const bool isCrashSectorRowTile = (rowTileIndex / 64) == 1452;
					const bool isCrashSectorColumnTile = (columnTileIndex / 64) == 1290;
					if (isCrashSectorRowTile && isCrashSectorColumnTile) {
						uint32_t artWord2 = readUpTo4Bytes(mobFile, MobConstants::ArtWord2Offset, MobConstants::ArtWord2Length);
						artWord2 = artWord2 << 0x10;
						std::cout << "art word 2: " << std::hex << artWord2 << std::dec << ". file: " << fileName << std::endl;
						const std::string art = SectorNPCReverser::getArtName(artWord2);
						const uint32_t tileInstanceId = (rowTileIndex % 64) + (columnTileIndex % 64) * 64;
						
						uint32_t artWord1 = readUpTo4Bytes(mobFile, MobConstants::ArtWord1Offset, MobConstants::ArtWord1Length);
						artWord1 = artWord1 << 0x10;
						std::cout << "art word 1: " << std::hex << artWord1 << std::dec << ". file: " << fileName << std::endl;
						const uint8_t paletteIndex = SectorNPCReverser::getPaletteIndex(artWord1);
						const uint8_t rotationIndex = SectorNPCReverser::getRotationIndex(artWord1);

						boost::json::object npcObj;
						npcObj["tileInstanceId"] = tileInstanceId;
						npcObj["textureName"] = art;
						npcObj["paletteIndex"] = paletteIndex;
						npcObj["rotationIndex"] = rotationIndex;
						npcs.push_back(npcObj);
					}
					mobFile.close();
				}
				else {
					std::cout << "Couldn't open the .mob file: " << fileName << std::endl;
				}
			}
		} while (FindNextFile(hFind, &data));
		
		const DWORD err = GetLastError();
		if (err == ERROR_NO_MORE_FILES) {
			std::cout << "No more files" << std::endl;
		}
		else {
			std::cout << "Unknown error. Code: " << err << std::endl;
		}
		FindClose(hFind);

		boost::json::object json;
		json["npcs"] = npcs;
		std::ofstream outFile("86570436012-npcs", std::ofstream::out);
		if (outFile.is_open()) {
			try {
				outFile << json << std::endl;
				outFile.flush();
			}
			catch (std::system_error& e) {
				if (outFile.is_open())
					outFile.close();
				std::cerr << e.code().message() << std::endl;
				throw;
			}
			outFile.close();
		}
	}

	std::cout << ".mob files found: " << mobFilesCount << std::endl;
	
	return 0;
}