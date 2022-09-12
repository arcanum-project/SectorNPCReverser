#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <boost/algorithm/string.hpp>

class SectorNPCReverser {
public:
	inline static const std::string getArtName(const uint32_t& artWord2) {
		const uint32_t shiftedArtWord2 = artWord2 >> 0x1C;
		if ((shiftedArtWord2 & shiftedArtWord2) != 0x0) {
			if (shiftedArtWord2 != 0x1) {
				if (shiftedArtWord2 != 0x3) {
					if (shiftedArtWord2 != 0x4) {
						if (shiftedArtWord2 != 0x7) {
							// critter
							if (shiftedArtWord2 == 0x2) {
								const uint32_t artPrefix2Index = (artWord2 >> 0x14) & 0xF;
								if (artPrefix2Index < 0x9) {
									const uint32_t artPrefix1Index = (artWord2 >> 0x18) & 0x7;
									const uint32_t isMale = (artWord2 >> 0x1B) & 0x1;
									const uint32_t genderArray[] = { 0x46, 0x4D }; // 0x46 for 'F', 0x4D for 'M'
									const uint32_t gender = genderArray[isMale];
									if (artPrefix2Index != 0x4) {
										if (artPrefix2Index != 0x6) {
											const uint32_t shiftedArtWord2_4 = (artWord2 >> 0x6) & 0x1F;
											const std::vector<uint16_t> artPrefixes1 = { 0x484D, 0x4446, 0x4748, 0x4847, 0x4546 };
											const uint16_t artPrefix1 = artPrefixes1.at(artPrefix1Index);
											const std::vector<uint16_t> artPrefixes2 = { 0x5557, 0x5631, 0x4C41, 0x434D, 0x504D, 0x5242, 0x5043, 0x424E, 0x4344 };
											uint16_t artPrefix2{};
											if (shiftedArtWord2_4 != 0x18) {
												artPrefix2 = artPrefixes2.at(artPrefix2Index);
											}
											else {
												artPrefix2 = 'XX';
											}
											const uint32_t artPrefix3Index = (artWord2 >> 0x13) & 0x1;
											const std::vector<uint8_t> artPrefixes3 = { 0x58, 0x53 }; // 0x58 for 'X', 0x53 for 'S'
											const uint8_t artPrefix3 = artPrefixes3[artPrefix3Index];
											const uint32_t artSuffix1Index = artWord2 & 0xF;
											const std::string artSuffix1Str = std::string("ABCDEFGHIJKXYNZ");
											uint8_t artSuffix1{};
											if (artSuffix1Index != 0x7) {
												artSuffix1 = artSuffix1Str.at(artSuffix1Index);
											}
											else if (artPrefix3Index == 0x1) {
												artSuffix1 = 0x44; // 0x44 = 'D'.
											}
											else {
												artSuffix1 = artSuffix1Str.at(artSuffix1Index);
											}
											const uint8_t artSuffix2 = 0x61; // 0x61 = 'a'
											std::string art = twoBytesToAscii(artPrefix1) + static_cast<char>(gender) + twoBytesToAscii(artPrefix2) + static_cast<char>(artPrefix3) + static_cast<char>(artSuffix1) + static_cast<char>(artSuffix2);
											boost::algorithm::to_lower(art);
											std::cout << "art: " << art << std::endl;
											return art;
										}
										else {
											std::cout << "Unknown artWord2. artPrefix2Index == 0x6. artWord2: " << std::hex << artWord2 << std::endl;
										}
									}
									else {
										std::cout << "Unknown artWord2. artPrefix2Index == 0x4. artWord2: " << std::hex << artWord2 << std::endl;
									}
								}
								else {
									std::cout << "Unknown artWord2. artPrefix2Index >= 0x9. artWord2: " << std::hex << artWord2 << std::endl;
								}
							}
							else if (shiftedArtWord2 != 0xC) {
								// unique_npc
								if (shiftedArtWord2 == 0xD) {
									const uint32_t artPrefixId = (artWord2 >> 0x14) & 0xFF;
									if (artPrefixId < 0x13) {
										const uint32_t shiftedArtWord2_6 = artPrefixId | 0xFFFFFFFF;
										if ((shiftedArtWord2_6 & shiftedArtWord2_6) != 0) {
											/*if (artPrefixId > 0x9) {
												if (artPrefixId > 0xE) {
													if (artPrefixId > 0x10) {
														if (artPrefixId >= 0x11) {
															
														}
														else {
															std::cout << "Unknown artWord2. unique_npc's artPrefixId < 0x11. artWord2: " << std::hex << artWord2 << std::endl;
														}
													}
													else {
														std::cout << "Unknown artWord2. unique_npc's artPrefixId <= 0x10. artWord2: " << std::hex << artWord2 << std::endl;
													}
												}
												else {
													std::cout << "Unknown artWord2. unique_npc's artPrefixId <= 0xE. artWord2: " << std::hex << artWord2 << std::endl;
												}
											}
											else {
												std::cout << "Unknown artWord2. unique_npc's artPrefixId <= 0x9. artWord2: " << std::hex << artWord2 << std::endl;
											}*/

											const uint32_t shiftedArtWord2_8 = (artWord2 >> 0x6) & 0x1F;
											const uint32_t artPrefix3Index = (artWord2 >> 0x13) & 0x1;
											const uint8_t artPrefixes3AsciiArray[] = { 0x58, 0x53 }; // 0x58 for 'X', 0x53 for 'S'
											const uint8_t artPrefix3 = artPrefixes3AsciiArray[artPrefix3Index];
											const uint32_t artSuffix1Index = artWord2 & 0xF;
											const std::string artSuffix1Str = std::string("ABCDEFGHIJKXYNZ");
											char artSuffix1{};
											if (artSuffix1Index != 0x7) {
												artSuffix1 = artSuffix1Str.at(artSuffix1Index);

											}
											else if (artPrefix3Index == 0x1) {
												artSuffix1 = 0x44; // 'D'
											}
											else {
												artSuffix1 = artSuffix1Str.at(artSuffix1Index);
											}
											const char artSuffix2 = 0x61; // 'a'
											const std::unordered_map<uint32_t, std::string> prefixes = uniqueNPCArtPrefixes();
											const std::unordered_map<uint32_t, std::string>::const_iterator iter = prefixes.find(artPrefixId);
											if (iter != prefixes.end()) {
												const std::string artPrefix = iter->second;
												std::string art = artPrefix + static_cast<char>(artPrefix3) + static_cast<char>(artSuffix1) + static_cast<char>(artSuffix2);
												boost::algorithm::to_lower(art);
												std::cout << "art: " << art << std::endl;
												return art;
											}
											else {
												std::cout << "Couldn't map unique_npc's artPrefixId to artPrefix. artPrefixId: " << std::dec << artPrefixId << ". artWord2: " << std::hex << artWord2 << std::endl;
											}
										}
										else {
											std::cout << "Unknown artWord2. unique_npc's (shiftedArtWord2_6 & shiftedArtWord2_6) == 0. artWord2: " << std::hex << artWord2 << std::endl;
										}
									}
									else {
										std::cout << "Unknown artWord2. unique_npc's artPrefixId >= 0x13. artWord2: " << std::hex << artWord2 << std::endl;
									}
								}
							}
							else {
								std::cout << "Unknown artWord2. shiftedArtWord2: " << std::hex << shiftedArtWord2 << ".artWord2: " << artWord2 << std::endl;
							}
						}
						else {
							std::cout << "Unknown artWord2. shiftedArtWord2 == 0x7. artWord2: " << std::hex << artWord2 << std::endl;
						}
					}
					else {
						std::cout << "Unknown artWord2. shiftedArtWord2 == 0x4. artWord2: " << std::hex << artWord2 << std::endl;
					}
				}
				else {
					std::cout << "Unknown artWord2. shiftedArtWord2 == 0x3. artWord2: " << std::hex << artWord2 << std::endl;
				}
			}
			else {
				std::cout << "Unknown artWord2. shiftedArtWord2 == 0x1. artWord2: " << std::hex << artWord2 << std::endl;
			}
		}
		else {
			std::cout << "Unknown artWord2. shiftedArtWord2 == 0. artWord2: " << std::hex << artWord2 << std::endl;
		}
		throw std::runtime_error("Couldn't parse artword");
	}

private:
	inline static const std::string twoBytesToAscii(const uint16_t& bytes) {
		uint8_t firstByte = bytes >> 0x8;
		uint8_t secondByte = bytes & 0xFF;
		const std::string asciiStr{ static_cast<char>(firstByte), static_cast<char>(secondByte) };
		return asciiStr;
	}

	static const std::unordered_map<uint32_t, std::string> uniqueNPCArtPrefixes() {
		return std::unordered_map<uint32_t, std::string>{
			std::make_pair(0, std::string("hmmbs")),
			std::make_pair(1, std::string("hmmtn")),
			std::make_pair(2, std::string("hmmvg")),
			std::make_pair(3, std::string("ghmvg")),
			std::make_pair(4, std::string("hmmki")),
			std::make_pair(5, std::string("ghmst")),
			std::make_pair(6, std::string("hmmgb")),
			std::make_pair(7, std::string("effvg")),
			std::make_pair(8, std::string("efmvg")),
			std::make_pair(9, std::string("ghmv2")),
			std::make_pair(10, std::string("ghfvg")),
			std::make_pair(11, std::string("hmfvg")),
			std::make_pair(12, std::string("dfmvg")),
			std::make_pair(13, std::string("effsl")),
			std::make_pair(14, std::string("efmax")),
			std::make_pair(15, std::string("hmmpn")),
			std::make_pair(16, std::string("ghfcd")),
			std::make_pair(17, std::string("hmfc2")),
			std::make_pair(18, std::string("hopuw")),
			std::make_pair(19, std::string("ayauw")),
			std::make_pair(20, std::string("dgnuw")),
			std::make_pair(21, std::string("gwtuw")),
			std::make_pair(22, std::string("hlbuw")),
			std::make_pair(23, std::string("kituw")),
			std::make_pair(24, std::string("krguw")),
			std::make_pair(25, std::string("lycuw")),
			std::make_pair(26, std::string("snwuw")),
			std::make_pair(27, std::string("kergn")),
			std::make_pair(28, std::string("Kr1uw")),
			std::make_pair(29, std::string("Kr2uw")),
			std::make_pair(30, std::string("Kr3uw")),
			std::make_pair(31, std::string("SHMuw")),
			std::make_pair(32, std::string("GLMuw")),
			std::make_pair(33, std::string("FM1uw")),
			std::make_pair(34, std::string("PH1uw")),
			std::make_pair(35, std::string("PH2uw")),
			std::make_pair(36, std::string("PH3uw")),
			std::make_pair(37, std::string("SWGuw")),
			std::make_pair(38, std::string("nakuw")),
			std::make_pair(39, std::string("VORuw"))
		};
	}
};

